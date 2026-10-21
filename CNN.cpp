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

int filter_size_x;
int filter_size_y;

class CNN {
private:
  std::vector<Filters> filters;
  Filters first_layer;
  

  std::vector<std::vector<double>> biases;
  std::vector<int> number_of_kernels_or_whatever_per_layer = {16, 36, 42, 58, 80, 45};
  std::vector<std::vector<Matrix>> darn_input_maps;

  inline double ReLU (double multipliedValue) {
    return (multipliedValue > 0) ? multipliedValue : 0.0;
  }
  //STILL IN PROGRESS!
  Image create_vector_to_input_from_this_darn_picturey_thing () {}
//WORK HERE
  

  Filters multiplyKernels (const std::vector<Filters> &thingamabob, const std::vector<std::vector<Matrix>> &input_maps, const std::vector<std::vector<double>> &biases) {
    if (input_image.empty() || thingamabob.empty()) {
      return {};
    }
    else {
      for(int layer_number = 0; layer_number < thingamabob.size(); layer_number++) {
        for (int no_of_filter = 0; no_of_filter < thingamabob[layer_number].size(); no_of_filter++) {
          for (int pixel_y = 0; pixel_y < image_y_dim - 2; pixel_y++) {
            int count_x = -1;
            int count_y = -1;
            for (int pixel_x = 0; pixel_x < image_x_dim - 2; pixel_x++) {
              count_x ++;
              count_y ++;
              double sum = biases[layer_number][no_of_filter];
              for (int no_of_channel = 0; no_of_channel < thingamabob[no_of_filter].size(); no_of_channel++) {
                for (int row = 0; row < filter_size_y; row++) {
                  for (int col = 0; col < filter_size_x; col++) {
                    
                    sum += thingamabob[layer_number][no_of_filter]/**[pixel_x][pixel_y]**/[no_of_channel][row][col] * input_maps[no_of_channel][pixel_x][pixel_y];
                  
                  } //work on putting the darn thing in the matrix
                }
              }
              darn_input_maps[layer + 1][no_of_filter][count_x][count_y] = sum;
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
        filters[ft][number_of_filters].resize(number_of_kernels_or_whatever_per_layer[ft -1]);
        for (int num_of_input_maps_per_filter_aka_channels = 0; num_of_input_maps_per_filter_aka_channels < number_of_kernels_or_whatever_per_layer[ft -1]; number_of_kernels_or_whatever_per_layer++) {
          filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels].resize(3);
          for (int row = 0; row < 3; row++){
            filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels][row].resize(3);
            for (int col = 0; col < 3; col++) {
              filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels][row][col] = randdouble(rng);
            }
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
