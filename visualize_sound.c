#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char * argv[]) {
  SF_INFO file_info;
  if (argc < 2) {
    printf("Usage:\n%s file.wav", argv[0]);
  }
  SNDFILE * file = sf_open(argv[1], SFM_READ, &file_info);

  int nb_samples = file_info.channels * file_info.frames;
  float * samples  = malloc(nb_samples*sizeof(float));
  sf_read_float(file, samples, nb_samples);

  FILE * gp = popen("gnuplot","w");
  fprintf(gp, "set term png\n");
  fprintf(gp, "set out \"waveform.png\"\n");
  fprintf(gp, "plot '-' with lines\n");

  for (int i=0; i < nb_samples; ++i)
    fprintf(gp, "%f\n",samples[i]);
  fprintf(gp,"e\n");

  free(samples);
  sf_close(file);

  return 0;
}
