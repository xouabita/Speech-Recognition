#include "../src/hmm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  HMM * model = new_HMM();
  assert( model->n_components == 5 );

  float transmat_prior[5][5] = {
    { 0.5 , 0.5 , 0.  , 0.  , 0.  },
    { 0.  , 0.5 , 0.5 , 0.  , 0.  },
    { 0.  , 0.  , 0.5 , 0.5 , 0.  },
    { 0.  , 0.  , 0.  , 0.5 , 0.5 },
    { 0.  , 0.  , 0.  , 0.  , 1.  },
  };
  float startprob_prior[5] = { 1., 0., 0., 0., 0. };

  for (int i = 0; i < model->n_components; i++) {
    assert( model->startprob[i] == 0. );
    assert( model->startprob_prior[i] == startprob_prior[i] );
    for (int j = 0; j < model->n_components; j++) {
      assert( model->transmat[i][j] == 0.);
      assert( model->transmat_prior[i][j] == transmat_prior[i][j]);
    }
  }

  delete_HMM(model);
  return 0;
}
