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

class CNN {
private:
  Filters filters;
  Filter 

  float ReLU (double multipliedValue) {
    if(multipliedValue > 0.0) {
      return multipliedValue;
    }
    if (multipliedValue <= 0) {
      return 0;
    }
  }
public:
  CNN () {
    filters.resize(16);

    for (int i = 0, i < 3, i++) {
      filters[i].resize(3);
      for (int channel = 0, channel < 3, channel++) {
        filters[i][channel].resize(3);
        for (int row = 0, row < 3, row++){
          filters[i][channel][row].resize(3);
          for (int col = 0, col < 3, col++) {
            filters[i][channel][row][col] = randdouble(rng);
          }
        }
      }
    }
  
};
