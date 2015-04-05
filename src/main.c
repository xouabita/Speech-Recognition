#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "pretreatment.h"
#include "gnuplot.h"
#include "signal_analysis.h"
int main (int argc, char * argv[]) {

  SF_INFO file_info;
  if (argc < 2) {
    printf("Usage:\n%s file.wav\n", argv[0]);
    return 1;
  }
  SNDFILE * file = sf_open(argv[1], SFM_READ, &file_info);

  int nb_samples  = file_info.channels * file_info.frames;
  int samplerate  = file_info.samplerate;
  float * samples = malloc(nb_samples*sizeof(float));

  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);
  print_signal (mono, file_info.frames, file_info.samplerate, argv[1], "mono.png");

  float * without_silence = silence (mono, file_info, 0.5);
  print_signal (without_silence, file_info.frames, file_info.samplerate, argv[1], "without_silence.png");

  float * preemphased = preemphase (without_silence, file_info);
  print_signal (preemphased, file_info.frames, file_info.samplerate, argv[1], "preemphase.png");

  Segments segments = segmentation(preemphased, file_info);
  int trame=segments.trame;
  int fft_length=512;
  int nb_per_trame=samplerate/50;

  complex float ** fft_result = fft(segments,fft_length);
  float **power_spectrum=cepstral(fft_result, trame, fft_length);
	print_graph(power_spectrum[15],fft_length,argv[1],"power_spectre.png");
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
  free(cepstral_coefficient);
  return 0;
}
