#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);

  FILE * gp = popen("gnuplot","w");
  fprintf(gp, "set term png\n");
  fprintf(gp, "set out \"waveform.png\"\n");
  fprintf(gp, "plot '-' with lines title \"%s\"\n", argv[1]);

  for (int i=1; i < nb_samples; i+=2)
    fprintf(gp, "%f\n",samples[i]);
  fprintf(gp,"e\n");

  free(samples);
  free(mono);
  sf_close(file);

  return 0;
}
