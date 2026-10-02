#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

std::random_device seed;
std::mt19937 rng(seed());
std::uniform_int_distribution<double> randint(0, 1);

using Matrix = std::vector<std::vector<double>>;
using Filter = std::vector<Matrix>;

class CNN {
private:
  Filter filters;

  float ReLU (double multipliedValue) {
    if(multipliedValue > 0.0) {
      return multipliedValue;
    }
    if (multipliedValue =< 0) {
      return 0;
    }
  }
public:
  CNN () {
    filters.resize(8);

    for (int i = 0, i++, i < 8) {
      double weightBase = randint(rng);
      weightBase = x;
      filters [i] = {
        {}
        }
      }
  
};
