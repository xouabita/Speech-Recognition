#include "hmm.h"
#include "kmeans.h"
#include "../NArr/src/narr.h"
#include <stdlib.h>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CONSTANTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define N_COMPONENTS 5
#define N_ITER       10
#define N_FEATURES   12

#define DATA_TRANSMAT {            \
  { 0.5 , 0.5 , 0.  , 0.  , 0.  }, \
  { 0.  , 0.5 , 0.5 , 0.  , 0.  }, \
  { 0.  , 0.  , 0.5 , 0.5 , 0.  }, \
  { 0.  , 0.  , 0.  , 0.5 , 0.5 }, \
  { 0.  , 0.  , 0.  , 0.  , 1.  }, \
}

#define DATA_STARTPROB { 1., 0., 0., 0., 0. }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// UTILS FUNCTIONS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float ** init_matrice (int n_components, float value[n_components][n_components]) {
  float ** result = malloc(sizeof(float*)*n_components);
  if (!value) {
    for (int i=0; i < n_components; i++) {
      result[i] = malloc(sizeof(float)*n_components);
      for (int j=0; j < n_components; j++) result[i][j] = 0.;
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// INIT/DELETE
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HMM * new_HMM () {
  HMM * model = malloc(sizeof(HMM));
  float DATA[N_COMPONENTS][N_COMPONENTS] = DATA_TRANSMAT;
  float STARTPROB[N_COMPONENTS]          = DATA_STARTPROB;

  model->n_components    = N_COMPONENTS;
  model->n_iter          = N_ITER;
  model->transmat        = init_matrice(model->n_components, NULL);
  model->transmat_prior  = init_matrice(model->n_components, DATA);
  model->startprob       = malloc(sizeof(float)*model->n_components);
  model->startprob_prior = malloc(sizeof(float)*model->n_components);
  for (int i=0; i < model->n_components; i++) {
    model->startprob_prior[i] = STARTPROB[i];
    model->startprob[i] = 0.;
  }
  return model;
}

void delete_HMM(HMM * model) {

  delete_mat(model->transmat, model->n_components);
  delete_mat(model->transmat_prior, model->n_components);
  free(model->startprob_prior);
  free(model->startprob);
  free(model);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// INTERACT WITH MODEL
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void _init (HMM * model, float *** obs) {
  float v = 1. / (float)model->n_components;
  for (int i=0; i < model->n_components; i++) {
    model->startprob[i] = v;
    for (int j=0; j < model->n_components; j++) {
      model->transmat[i][j] = v;
    }
  }
  model->n_features = N_FEATURES;
  KMeans means      = new_KMeans(model->n_components);
  KMeans_fit(means,obs[0]);
  model->_means_ = means.clusters_centers_;
}

struct sufficient_stats_t _init_suff_stats(int n_components, int n_features) {
  struct sufficient_stats_t stats;
  stats.nobs  = 0;
  stats.start = malloc(sizeof(float)*n_components);
  stats.post  = malloc(sizeof(float)*n_components);

  for (int i=0; i < n_components; i++) {
    stats.start[i] = 0.;
    stats.post[i]  = 0.;
  }

  stats.trans      = init_matrice(n_components, NULL);
  stats.obs        = malloc( sizeof(float*) * n_components );
  stats.square_obs = malloc( sizeof(float*) * n_components );
  for (int i=0; i < n_components; i++) {
    stats.obs[i] = malloc( sizeof(float) * n_features);
    stats.square_obs[i] = malloc( sizeof(float) * n_features);
    for (int j=0; j < n_features; j++) {
      stats.obs[i][j]        = 0.;
      stats.square_obs[i][j] = 0.;
    }
  }
  return stats;
}

void _del_suff_stats(HMM * model, struct sufficient_stats_t stats) {

  // Free 1-dim array
  free(stats.start);
  free(stats.post);

  // Free 2-dim arrays
  delete_mat(stats.trans, model->n_components);
  delete_mat(stats.obs, model->n_components);
  delete_mat(stats.square_obs, model->n_components);
}

void fit_HMM (HMM * model, float *** obs) {

  // Initialize transmat & startprob
  _init(model,obs);

  for (int i=0; i < model->n_iter; i++) {
    struct sufficient_stats_t stats = _init_suff_stats(model->n_components, model->n_features);
    float curr_logprob = 0.;
    int len_data = NArr_len(obs);
    for (int j=0; j < len_data; j++) {
      float ** seq = obs[i];
    }
    _del_suff_stats(model,stats);
  }
}
