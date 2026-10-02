#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using Matrix = std::vector<std::vector<double>>;

class CNN {
private:
  Matrix Weights_Matrix;
  int filersize;

  float ReLU (float multipliedValue) {
    if(multipliedValue > 0.0) {
      return multipliedValue;
    }
    if (multipliedValue < 0) {
      return 0;
    }
  }
public:
  
};
