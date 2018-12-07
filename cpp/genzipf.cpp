#include "cstdlib"
#include "math.h"
#include <assert.h>
#include <vector>
#include "genzipf.h"

using namespace std;

GenZipf::GenZipf(double alpha_, int n_) : alpha(alpha_), n(n_){
    double c = 0;
    for (int i=1; i<=n; i++)
      c = c + (1.0 / pow((double) i, alpha));
    c = 1.0 / c;

    sum_probs.push_back(0);
    for (int i=1; i<=n; i++) {
      sum_probs.push_back(sum_probs.back() + c / pow((double) i, alpha));
    }
}


int GenZipf::get() {
  double z;
  do {
    z = (float (rand()))/(float (RAND_MAX ));
  } while ((z == 0) || (z == 1));

  int zipf_value = 0;
  int low, high, mid;
  low = 1, high = n;

  while (low <= high) {
    mid = floor((low+high)/2);
    if (sum_probs[mid] >= z && sum_probs[mid-1] < z) {
      zipf_value = mid;
      break;
    } else if (sum_probs[mid] >= z) {
      high = mid-1;
    } else {
      low = mid+1;
    }
  }

  assert((zipf_value >=1) && (zipf_value <= n));

  return(zipf_value);
}

// Adapted from https://stackoverflow.com/questions/9983239/how-to-generate-zipf-distributed-numbers-efficiently
