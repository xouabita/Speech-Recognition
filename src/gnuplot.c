#include "gnuplot.h"
#include <stdio.h>

// save a graph with an array of float
void print_graph (float * data, int data_size, char * graph_name, char * png_name) {
  FILE * gp = popen("gnuplot","w");
  fprintf(gp, "set term png\n");
  fprintf(gp, "set out \"%s\"\n", png_name);
  fprintf(gp, "set yrange [-1:1]\n");
  fprintf(gp, "set xrange [0:%d]\n", data_size);
  fprintf(gp, "plot '-' with lines title \"%s\"\n", graph_name);

  for (int i=0; i < data_size; ++i)
    fprintf(gp, "%f\n", data[i]);
  fprintf(gp,"e\n");

  fflush(gp);
  pclose(gp);
}
