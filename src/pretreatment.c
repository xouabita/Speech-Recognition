#include <sndfile.h>
#include <stdlib.h>
#include <math.h>
#include "pretreatment.h"

float * make_mono (float * data, SF_INFO file_info) {
  float * result = malloc(file_info.frames*sizeof(float));
  int nb_channels = file_info.channels;

  for (int i=0; i < file_info.frames-nb_channels; i++) {
    float frame = 0;
    for (int j=0; j < nb_channels; j++) {
      frame += data[i*nb_channels+j];
    }
    result[i] = frame / (float)nb_channels;
  }

  return result;
}

float * silence (float * data, SF_INFO file_info, float threshold) {
  float * result = malloc(file_info.frames*sizeof(float));

  for (int i = 0; i < file_info.frames; ++i) {
    if (data[i] > threshold || data[i] < threshold) result[i] = data[i];
    else result[i] = 0;
  }

  return result;
}

float * preemphase (float * data, SF_INFO file_info) {
  float * result = malloc(file_info.frames*sizeof(float));

  result[0] = data[0];
  for (int i=0; i < file_info.frames; ++i) {
    result[i] = data[i] - 0.9 * data[i-1];
  }

  return result;
}

float ** segmentation (float * data, SF_INFO file_info) {

  int samplerate  = file_info.samplerate/50;
  int trame       = (file_info.frames/samplerate)+2;
  float ** result = malloc(trame * sizeof(float*));
  for (int i=0; i<trame; ++i) {
    result[i] = malloc(samplerate*sizeof(float));
  }

  int k = 0;
  for (int i=0; i<file_info.frames; i++) {
    if (i % samplerate == 0) k++;
    result[k][i % samplerate] = data[i];
  }

  int   n = samplerate/(file_info.frames-1);
  float w = 0.54f - 0.46f * cosf(n*3.14159265358979323846f);
  for (int i=0; i < trame; i++) {
    for (int j=0; j<samplerate; j++) {
      result[i][j]*=w;
    }
  }

  return result;
}
