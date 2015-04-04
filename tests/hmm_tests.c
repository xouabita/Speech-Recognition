#include "../src/hmm.h"

int main() {
  HMM * model = new_HMM(5);
  delete_HMM(model);

  return 0;
}
