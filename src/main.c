#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "pretreatment.h"
#include "gnuplot.h"
#include "signal_analysis.h"
#include "../NArr/src/narr.h"
#include "dtw.h"

double ** mfcc (char * file_str) {
  SF_INFO file_info;
  SNDFILE * file = sf_open(file_str, SFM_READ, &file_info);

  int nb_samples  = file_info.channels * file_info.frames;
  int samplerate  = file_info.samplerate;
  float * samples = malloc(nb_samples*sizeof(float));

  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);

  float * without_silence = silence (mono, file_info, 0.5);

  float * preemphased = preemphase (without_silence, file_info);

  Segments segments = segmentation(preemphased, file_info);
  int trame=segments.trame;
  int fft_length=512;
  int nb_per_trame=samplerate/50;

  complex float ** fft_result = fft(segments,fft_length);
  float **power_spectrum=cepstral(fft_result, trame, fft_length);
  double **cepstral_coefficient=coef_cep(fft_result, fft_length, trame, samplerate);

  for(int i=0; i<trame;i++)
    for(int j=0;j<13;j++)
      printf("%d %d %f \n",i,j,cepstral_coefficient[i][j]);

  free(samples);
  free(mono);
  free(without_silence);
  free(preemphased);
  free(segments.data);
  free(fft_result);

  return cepstral_coefficient;
}

int main (int argc, char * argv[]) {

  double *** mfccs_oui = new_NArr(sizeof(double*),3);
  double *** mfccs_non = new_NArr(sizeof(double*),3);

  printf("Learning....\n");

  mfccs_oui[0] = mfcc("./data/training/OUI/1.wav");
  mfccs_oui[1] = mfcc("./data/training/OUI/2.wav");
  mfccs_oui[2] = mfcc("./data/training/OUI/3.wav");

  mfccs_non[0] = mfcc("./data/training/NON/1.wav");
  mfccs_non[1] = mfcc("./data/training/NON/2.wav");
  mfccs_non[2] = mfcc("./data/training/NON/3.wav");

  printf("Testing...\n");

  double ** mfcc_oui = mfcc("oui.wav");
  double ** mfcc_non = mfcc("non.wav");

  printf("OUI: \n");
  printf("oui_1: %lf\n", dtw_distance(mfccs_oui[0], mfcc_oui) );
  printf("oui_2: %lf\n", dtw_distance(mfccs_oui[1], mfcc_oui) );
  printf("oui_3: %lf\n", dtw_distance(mfccs_oui[2], mfcc_oui) );

  return 0;
}
