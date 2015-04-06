#ifndef KMEANS_H_
#define KMEANS_H_

typedef struct kmeans_t {
  int n_clusters;
} KMeans;

KMeans new_KMeans(int n_clusters);
void KMeans_fit(KMeans means, float ** obs);

#endif
