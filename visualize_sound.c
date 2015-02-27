#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

// Take sound data with any amounts of channels and return a mono
// data by doing the average between the two channels
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

int main (int argc, char * argv[]) {
  SF_INFO file_info;
  if (argc < 2) {
    printf("Usage:\n%s file.wav\n", argv[0]);
    return 1;
  }
  SNDFILE * file = sf_open(argv[1], SFM_READ, &file_info);

  int nb_samples = file_info.channels * file_info.frames;
  float * samples  = malloc(nb_samples*sizeof(float));
  int samplerate = file_info.samplerate/50;
  int trame = (nb_samples/samplerate)+2;
  float ** segmentation;
  segmentation=malloc(trame * sizeof(float*));
  for(int i=0; i<trame; i++)
    {
    segmentation[i]=malloc(samplerate*sizeof(float));
    }
  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);

  int k=0;
  printf("%d\n",nb_samples);
  for(int i=0; i<nb_samples; i++){
    if(i % samplerate==0)
    {
      k++;
    }
    segmentation[k][i % samplerate]=samples[i];
  }

  //fenetrage
  float n= samplerate/(nb_samples-1);
  float w=0.54f - 0.46f* cosf(n*M_PI);
  for(int i=0; i< trame; i++)
    for(int j=0; j<samplerate;j++)
    {
      segmentation[i][j]*=w;
    }
  //fenetrage

  FILE * gp = popen("gnuplot","w");
  fprintf(gp, "set term png\n");
  fprintf(gp, "set out \"waveform.png\"\n");
  fprintf(gp, "plot '-' with lines title \"%s\"\n", argv[1]);

  for (int i=0; i < nb_samples; ++i)
    fprintf(gp, "%f\n",samples[i]);
  fprintf(gp,"e\n");
  free(samples);
  free(mono);
  for(int i=0; i<trame;i++)
    free(segmentation[i]);
  free(segmentation);
  sf_close(file);

  return 0;
}
