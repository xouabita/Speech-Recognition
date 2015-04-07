#include <math.h>
#include <complex.h>
#include <string.h>
#include "mfcc.h"
#include "../NArr/src/narr.h"

#define PI 3.141592653589793238462

struct MFCC {
  double ** mel;
  int     * melstart;
  int     * mellength;
};

void filter(double * signal) {
  int len = NArr_len(signal);
  for (int i = 1; i < len; i++) signal[i] -= .95 * signal[i-1];
}

double ** frame (double * signal, int N, int M) {
  int n = NArr_len(signal);
  int num_blocks = n / N;

  int maxblockstart = n - N;
  int lastblockstart = maxblockstart - (maxblockstart % M);
  int numbblocks = (lastblockstart)/M + 1;

  double ** res = new_NArr(sizeof(double*),numbblocks);
  for (int i=0; i < 0; i++) {
    res[i] = new_NArr(sizeof(double),N);
    for (int j=0; j < N; j++) {
      res[i][j] = signal[i*M+j];
    }
  }

  return res;
}

double get_hamming_frame(double * frame, double * result) {

  int len = NArr_len(frame);
  result = new_NArr(sizeof(double), len);
  double max = 0;
  for (int i=0; i < len; i++) {
    double value = 0.54 - 0.46 * cosf(2 * PI * i / (len - 1));
    result[i] = value;
    if (value > max) max = value;
  }

  return max;
}

void hamming_window(double ** frames, double * max) {
  double * hamming_res;
  *max = get_hamming_frame(frames[0],hamming_res);

  int len_i = NArr_len(frames);
  int len_j = NArr_len(frames[0]);

  for (int i=0; i < len_i; i++)
    for (int j=0; j < len_j; j++)
      frames[i][j] = frames[i][j] * hamming_res[j];

  delete_NArr(hamming_res);
}

void mel_frame(struct MFCC * mfcc, int fft_size, int samplerate) {

  double fmax;
  double dphi;
  double fsample;
  double freq;
  double temp[fft_size/2];

  fmax = 2595*log10(8000.0f/700+1);
  dphi = fmax / 17;
  freq = (double)samplerate/fft_size;

  for (int i = 0; i < 16; i++) {
    mfcc->melstart[i]=fft_size/2;
    mfcc->mellength[i]=0;
    memset(temp,0,sizeof(double)*fft_size/2);

    for (int j = 0; j < fft_size/2; j++) {
      mfcc->mel[i] = new_NArr(sizeof(double), mfcc->mellength[i]);
      fsample = 2595*log10(freq*j/700 + 1);

      if ((dphi*i <= fsample) && (fsample < dphi*(i+1))) temp[j] = (fsample-dphi*i)/(dphi*(i+1)-dphi*i);
      if ((dphi*(i+1) <= fsample) && (fsample < dphi*(i+2))) temp[j] = (fsample-dphi*(i+2))/(dphi*(i+1)-dphi*(i+2));
      if ((temp[j] != 0) && (mfcc->melstart[i] > j)) mfcc->melstart[i] = j;
      if (temp[j] != 0) mfcc->mellength[i]++;
    }

    delete_NArr(mfcc->mel[i]);
    mfcc->mel[i] = new_NArr(sizeof(double), mfcc->mellength[i]);
    for (int j = 0; j < mfcc->mellength[i]; j++ ) {
      mfcc->mel[i][j] = temp[mfcc->melstart[i]+j];
    }
  }
}

complex double ** convertToComplex(double ** frames, int fft_size) {

  int len = NArr_len(frames);
  complex double ** result = new_NArr(sizeof(complex double*), len);

  for (int i=0; i < len; i++) {
    result[i] = new_NArr(sizeof(complex double), fft_size);
    for (int j=0; j < len; j++) {
      result[i][j] = frames[i][j] + I * frames[i][j];
    }
  }

  return result;
}

double ** mfcc(double * signal, int samplerate) {

  int M = 100;
  int N = 256;
  double max = 0;

  struct MFCC mfcc;
  mfcc.mel       = new_NArr(sizeof(double*),16);
  mfcc.melstart  = new_NArr(sizeof(double),16);
  mfcc.mellength = new_NArr(sizeof(double),16);

  filter(signal);
  double ** frames = frame(signal,N,M);

  hamming_window(frames,&max);
  mel_frame(&mfcc, N, samplerate);

  complex double ** fft_vars = convertToComplex(frames, N);

  return frames;
}
