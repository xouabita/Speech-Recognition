#ifndef HMM_H_
#define HMM_H_

typedef struct hmm_t {
  int n_components;  // Number of states in the model
  float ** transmat; // Matrix of transition probabilities between states.
  float *  startprob;
  float ** transmat_prior;
  float *  startprob_prior;
  int n_mix;
  int n_iter;
  float threshold;
} HMM;

HMM * new_HMM    ();
void  delete_HMM (HMM * model);

#endif // HMM_H_
