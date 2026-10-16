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

int image_y_dim = 128;
int image_x_dim = 128;

class CNN {
private:
  std::vector<Filters> filters;
  Filter Final_layer;

  std::vector<std::vector<double>> biases;
  std::vector<int> number_of_kernels_or_whatever_per_layer = {16, 36, 42, 58, 80, 45};

  inline double ReLU (double multipliedValue) {
    return (multipliedValue > 0) ? multipliedValue : 0.0;
  }
  //STILL IN PROGRESS!
  Image create_vector_to_input_from_this_darn_picturey_thing () {}

  Filters multiplyKernels (const Filters &thingamabob, const Image &input_image) {
    for (int no_of_filter = 0; no_of_filter < thingamabob.size(); no_of_filter++) {
      for (int no_of_channel = 0; no_of_channel < thingamabob[filter].size(); no_of_channel++) {
        double sum = 0.0;
        sum += thingamabob[no_of_filter][no_of_channel] * input_image[
      }
    }
  }
public:
  CNN () {
    filters.resize(number_of_kernels_or_whatever_per_layer.size());
    biases.resize(number_of_kernels_or_whatever_per_layer.size());
    //number of layers
    for (int ft = 0; ft <  6; ft++) {
      filters[ft].resize(number_of_kernels_or_whatever_per_layer[ft]);
      biases[ft].resize(number_of_kernels_or_whatever_per_layer[ft]);
      for (int number_of_filters = 0; number_of_filters < number_of_kernels_or_whatever_per_layer[ft]; number_of_filters++) {
        filters[ft][number_of_filters].resize(3);
        biases[ft][number_of_filters] = randdouble(rng);
        for (int channel = 0; channel < 3; channel++) {
          filters[ft][number_of_filters][channel].resize(3);
          for (int row = 0; row < 3; row++){
            filters[ft][number_of_filters][channel][row].resize(3);
            for (int col = 0; col < 3; col++) {
              filters[ft][number_of_filters][channel][row][col] = randdouble(rng);
            }
          }
        }
      }
    }
    
  }
};
