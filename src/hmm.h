#ifndef HMM_H_
#define HMM_H_

struct sufficient_stats_t {
  int nobs;
  float *  start;
  float ** trans;
};

typedef struct hmm_t {
  int n_components;  // Number of states in the model
  float ** transmat; // Matrix of transition probabilities between states.
  float *  startprob;
  float ** transmat_prior;
  float *  startprob_prior;
  int n_iter;
  float threshold;
} HMM;

// Init/Delete model

HMM * new_HMM    (); // Create a new HMM model with the bakis model
void  delete_HMM (HMM * model);

//Interact w/ model

void fit_HMM(HMM * model, float ** data);

#endif // HMM_H_
