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
  Filters filters;
  Filters first_layer;

  std::vector<std::vector<double>> biases;
  std::vector<int> number_of_kernels_or_whatever_per_layer = {16, 36, 42, 58, 80, 45};

  inline double ReLU (double multipliedValue) {
    return (multipliedValue > 0) ? multipliedValue : 0.0;
  }
  //STILL IN PROGRESS!
  Image create_vector_to_input_from_this_darn_picturey_thing () {}

  Filters multiplyKernels_layer_one (const Filters &thingamabob, const Image &input_image const &std::vector<std::vector<double>> biases, int stride, int padding) {
    if (input_image.empty() || thingamabob.empty()) {
      return {};
    }
    else if {
      for (int no_of_filter = 0; no_of_filter < thingamabob.size(); no_of_filter++) {
        for (int no_of_channel = 0; no_of_channel < thingamabob[filter].size(); no_of_channel++) {
          for (int pixel_x = 0; pixel_x < image_x_dim; pixel_x++) {
            for (int pixel_y = 0; pixel_y < image_y_dim; pixel_y++) {
              double sum = 0.0;
              sum += thingamabob[no_of_filter][no_of_channel] * input_image[pixel_x][pixel_y];
            }
          }
        }
      } 
    }    
  }
public:
  CNN () {
    filters.resize(number_of_kernels_or_whatever_per_layer.size() - 1);
    biases.resize(number_of_kernels_or_whatever_per_layer.size());

    for (int layer = 0; layer < number_of_kernels_or_whatever_per_layer.size(); layer++) {
      biases[layer].resize(number_of_kernels_or_whatever_per_layer[layer]);
      for (int num_filter = 0; num_filter < number_of_kernels_or_whatever_per_layer[layer]; num_filter++) {
        biases[layer][num_filter] = randdouble(rng);
      }
    }
    
    //number of layers
    for (int ft = 1; ft <  5; ft++) {
      filters[ft].resize(number_of_kernels_or_whatever_per_layer[ft]);
      for (int number_of_filters = 0; number_of_filters < number_of_kernels_or_whatever_per_layer[ft]; number_of_filters++) {
        filters[ft][number_of_filters].resize(3);
        for (int row = 0; row < 3; row++){
          filters[ft][number_of_filters][row].resize(3);
          for (int col = 0; col < 3; col++) {
            filters[ft][number_of_filters][row][col] = randdouble(rng);
          }
        }
      }
    }
    
    first_layer.resize(number_of_kernels_or_whatever_per_layer[0]);

    for (int filter = 0; filter < number_of_kernels_or_whatever_per_layer[0]; filter++) {
      first_layer[filter].resize(3);
      for (int channel = 0; channel < 3; channel++) {
        first_layer[filter][channel].resize(3);
        for (int row = 0; row < 3; row++) {
          first_layer[filter][channel][row].resize(3);
          for (int col = 0; col < 3; col++) {
            first_layer[filter][channel][row][col] = randdouble(rng);
          }
        }
      }
    }
  }
};
