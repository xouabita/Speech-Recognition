#include "hmm.h"
#include <stdlib.h>

HMM * new_HMM (int n_components) {
  HMM * model = malloc(sizeof(HMM));

  model->n_components = n_components;
  model->transmat = malloc(sizeof(float*)*n_components);
  for (int i=0; i < n_components; i++) {
    model->transmat[i] = malloc(sizeof(float)*n_components);
  }
  return model;
}

void delete_HMM(HMM * model) {

  for (int i=0; i < model->n_components; i++) {
    free(model->transmat[i]);
  }
  free(model->transmat);
  free(model);
}
