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
  Filters filters;
  Filters filters_but_for_layer_two;
  FIlters filters_but_for_layer_three;
  
  std::vector<double> biases;
  std::vector<double> biases_2;
  std::vector<double> biases_3;  

  float ReLU (double multipliedValue) {
    return (multipliedValue > 0) ? double multipliedValue : double 0.0;
  }

  Matrix multiplyKernels (filters)
public:
  CNN () {
    filters.resize(16);
    biases.resize(16);

    for (int i = 0; i < 16; i++) {
      filters[i].resize(3);
      biases[i] = randdouble(rng);
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

    filters_but_for_layer_two.resize(12);
    biases_2.resize(12);

    for (int i = 0; i < 12; i++) {
      filters_but_for_layer_two[i].resize(3);
      biases_2[i] = randdouble(rng);
      for (int channel = 0; channel < 3; channel++) {
        filters_but_for_layer_two[i][channel].resize(3);
        for (int row = 0; row < 3; row++){
          filters_but_for_layer_two[i][channel][row].resize(3);
          for (int col = 0; col < 3; col++) {
            filters_but_for_layer_two[i][channel][row][col] = randdouble(rng);
          }
        }
      }
    }

    filters_but_for_layer_three.resize(12);
    biases_3.resize(12);

    for (int i = 0; i < 4; i++) {
      filters_but_for_layer_three[i].resize(3);
      biases_2[i] = randdouble(rng);
      for (int channel = 0; channel < 3; channel++) {
        filters_but_for_layer_three[i][channel].resize(3);
        for (int row = 0; row < 3; row++){
          filters_but_for_layer_three[i][channel][row].resize(3);
          for (int col = 0; col < 3; col++) {
            filters_but_for_layer_three[i][channel][row][col] = randdouble(rng);
          }
        }
      }
    }
  }  
};
