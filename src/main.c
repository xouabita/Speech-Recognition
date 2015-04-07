#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "gnuplot.h"
#include "mfcc.h"
#include "../NArr/src/narr.h"
#include "dtw.h"

double ** do_mfcc (char * file_str) {
  SF_INFO file_info;
  SNDFILE * file = sf_open(file_str, SFM_READ, &file_info);

  int nb_samples   = file_info.channels * file_info.frames;
  int samplerate   = file_info.samplerate;
  double * samples = new_NArr(sizeof(double),nb_samples);

  sf_read_double(file, samples, nb_samples);
  return mfcc(samples,file_info.samplerate);
}

int main (int argc, char * argv[]) {

  double *** mfccs_oui = new_NArr(sizeof(double*),3);
  double *** mfccs_non = new_NArr(sizeof(double*),3);

  printf("Learning....\n");

  mfccs_oui[0] = do_mfcc("./data/training/OUI/1.wav");
  mfccs_oui[1] = do_mfcc("./data/training/OUI/2.wav");
  mfccs_oui[2] = do_mfcc("./data/training/OUI/3.wav");

  mfccs_non[0] = do_mfcc("./data/training/NON/1.wav");
  mfccs_non[1] = do_mfcc("./data/training/NON/2.wav");
  mfccs_non[2] = do_mfcc("./data/training/NON/3.wav");

  printf("Testing...\n\n\n");

  double ** mfcc_oui = do_mfcc("oui.wav");
  double ** mfcc_non = do_mfcc("non.wav");

  printf("Testing OUI...\n\n");
  printf(" -> oui_1: %lf\n", dtw_distance(mfcc_oui,mfccs_oui[0]));
  printf(" -> oui_2: %lf\n", dtw_distance(mfcc_oui,mfccs_oui[1]));
  printf(" -> oui_3: %lf\n", dtw_distance(mfcc_oui,mfccs_oui[2]));
  printf(" -> non_1: %lf\n", dtw_distance(mfcc_oui,mfccs_non[0]));
  printf(" -> non_2: %lf\n", dtw_distance(mfcc_oui,mfccs_non[1]));
  printf(" -> non_3: %lf\n", dtw_distance(mfcc_oui,mfccs_non[2]));

  printf("\nTesting NON...\n\n");
  printf(" -> oui_1: %lf\n", dtw_distance(mfcc_non,mfccs_oui[0]));
  printf(" -> oui_2: %lf\n", dtw_distance(mfcc_non,mfccs_oui[1]));
  printf(" -> oui_3: %lf\n", dtw_distance(mfcc_non,mfccs_oui[2]));
  printf(" -> non_1: %lf\n", dtw_distance(mfcc_non,mfccs_non[0]));
  printf(" -> non_2: %lf\n", dtw_distance(mfcc_non,mfccs_non[1]));
  printf(" -> non_3: %lf\n", dtw_distance(mfcc_non,mfccs_non[2]));

  return 0;
}
