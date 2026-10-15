#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

std::random_device seed;
std::mt19937 rng(seed());
std::uniform_real_distribution<double> randdouble(-1.0, 1.0);

using Matrix = std::vector<std::vector<double>>;
using Filter = std::vector<Matrix>;
using Filters = std::vector<Filter>;
using Image = std::vector<Matrix>;

class CNN {
private:
  std::vector<Filters> filters;
  
  std::vector<std::vector<double>> biases;
  std::vector<int> number_of_kernels_or_whatever_per_layer = {16, 36, 42, 58, 80, 45};

  float ReLU (float multipliedValue) {
    return (multipliedValue > 0) ? multipliedValue : 0.0;
  }
  //STILL IN PROGRESS!
  Matrix multiplyKernels (filters) {
  }
public:
  CNN () {
    for (int ft = 0; ft <  6; ft++) {
      for (int number_of_filters = 0; number_of_filters < number_of_kernels_or_whatever_per_layer[ft]; number_of_filters++) {
        filters.resize(number_of_kernels_or_whatever_per_layer[ft]);
        biases.resize(number_of_kernels_or_whatever_per_layer[ft]);   
        filters[number_of_kernels_or_whatever_per_layer[ft]].resize(3);
        biases[number_of_kernels_or_whatever_per_layer[ft]] = randdouble(rng);
        for (int channel = 0; channel < 3; channel++) {
          filters[i][channel].resize(3);
          for (int row = 0; row < 3; row++){
            filters[i][channel][row].resize(3);
            for (int col = 0; col < 3; col++) {
              filters[i][channel][row][col] = randdouble(rng);
            }
          }
        }
      }
    }
  }
};
