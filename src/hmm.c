#include "hmm.h"
#include <stdlib.h>

#define N_COMPONENTS 5

#define DATA_TRANSMAT {            \
  { 0.5 , 0.5 , 0.  , 0.  , 0.  }, \
  { 0.  , 0.5 , 0.5 , 0.  , 0.  }, \
  { 0.  , 0.  , 0.5 , 0.5 , 0.  }, \
  { 0.  , 0.  , 0.  , 0.5 , 0.5 }, \
  { 0.  , 0.  , 0.  , 0.  , 1.  }, \
}

#define DATA_STARTPROB { 1., 0., 0., 0., 0. }

float ** init_matrice (int n_components, float value[n_components][n_components]) {
  float ** result = malloc(sizeof(float*)*n_components);
  if (!value) {
    for (int i=0; i < n_components; i++) {
      result[i] = malloc(sizeof(float)*n_components);
    }
  }
  else {
    for (int i=0; i < n_components; i++) {
      result[i] = malloc(sizeof(float)*n_components);
      for (int j=0; j < n_components; j++) result[i][j] = value[i][j];
    }
  }
  return result;
}

void delete_mat (float ** mat, int n_components) {
  for (int i=0; i < n_components; i++) {
    free(mat[i]);
  }
  free(mat);
}

HMM * new_HMM () {
  HMM * model = malloc(sizeof(HMM));
  float DATA[N_COMPONENTS][N_COMPONENTS] = DATA_TRANSMAT;
  float STARTPROB[N_COMPONENTS]          = DATA_STARTPROB;

  model->n_components   = N_COMPONENTS;
  model->transmat       = init_matrice(model->n_components, NULL);
  model->transmat_prior = init_matrice(model->n_components, DATA);
  model->startprob      = malloc(sizeof(float)*model->n_components);
  model->transmat_prior = malloc(sizeof(float)*model->n_components);
  for (int i=0; i < model->n_components; i++) model->startprob_prior[i] = STARTPROB[i];
  return model;
}

void delete_HMM(HMM * model) {

  delete_mat(model->transmat, model->n_components);
  delete_mat(model->transmat_prior, model->n_components);
  free(model->startprob_prior);
  free(model->startprob);
  free(model);
}
