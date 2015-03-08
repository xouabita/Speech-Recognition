#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "pretreatment.h"
#include "gnuplot.h"

int main (int argc, char * argv[]) {

  SF_INFO file_info;
  if (argc < 2) {
    printf("Usage:\n%s file.wav\n", argv[0]);
    return 1;
  }
  SNDFILE * file = sf_open(argv[1], SFM_READ, &file_info);

  int nb_samples  = file_info.channels * file_info.frames;
  float * samples = malloc(nb_samples*sizeof(float));

  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);

  float * without_silence = silence (mono, file_info, 0.1);

  float * preemphased = preemphase (without_silence, file_info);

  Segments segments = segmentation(preemphased, file_info);

  complex float ** fft_result = fft(segments);

  free(samples);
  free(mono);
  free(without_silence);
  free(preemphased);
  free(segments.data);
  free(fft_result);

  return 0;
}
