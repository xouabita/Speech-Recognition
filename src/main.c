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
  print_signal (mono, file_info.frames, file_info.samplerate, argv[1], "mono.png");

  float * without_silence = silence (mono, file_info, 0.1);
  print_signal (without_silence, file_info.frames, file_info.samplerate, argv[1], "without_silence.png");

  float * preemphased = preemphase (without_silence, file_info);
  print_signal (preemphased, file_info.frames, file_info.samplerate, argv[1], "preemphase.png");

  Segments segments = segmentation(preemphased, file_info);

  // Print all segments
  for (int i=0; i < segments.trame; ++i) {
    char buffer[100];
    sprintf(buffer,"segment_%d.png", i);
    print_graph(segments.data[i], segments.samplerate, argv[1], buffer);
  }

  complex float ** fft_result = fft(segments);

  free(samples);
  free(mono);
  free(without_silence);
  free(preemphased);
  free(segments.data);
  free(fft_result);

  return 0;
}
