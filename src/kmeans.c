#include "kmeans.h"

KMeans new_KMeans (int n_clusters) {
  KMeans means;
  means.n_clusters = n_clusters;
  return means;
}

void KMeans_fit(KMeans means, float ** obs) {
  
}

void kmeans(float ** X) {
  int    n_clusters = 8;
  int    n_init     = 10;
  int    max_iter   = 300;
  double tol        = 1e-4;
}
