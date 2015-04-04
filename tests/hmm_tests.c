#include "../src/hmm.h"
#include <assert.h>

int main() {
  HMM * model = new_HMM();
  assert( model->n_components == 5 );
  delete_HMM(model);

  return 0;
}
