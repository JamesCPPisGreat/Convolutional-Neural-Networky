#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

/**This code is not meant to function as a real Convolutional Neural Network would, but show how they are structured
and how they calculate and predict.
A real-world CNN would utlilize a deep learning framework, using tensors as opposed to nested vectors.
To be clear, this can function as a CNN, but it is not optimized for performance and is not suitable for
real-world applications. It is meant to be a learning tool for understanding the basic concepts of CNNs.
THIS WAS CODED FOR EDUCATIONAL PURPOSES ONLY BY A REAL HUMAN BEING. I HAVE NOT USED ANY AI TOOLS TO WRITE 
THIS CODE. I HAVE WRITTEN THIS CODE MYSELF, WITH THE EXCEPTION OF A FEW AUTOCOMPLETED LINES. I do not like
using AI tools to write code, as I believe it is important to understand the underlying concepts and logic behind the code.
Enjoy! (The goofy names are a result of my frustration with the complexity of CNNs in raw C++ and my desire to make the 
code more relatable and less intimidating.)
*/

//Random number generator for initializing weights and biases
std::random_device seed;
std::mt19937 rng(seed());
std::uniform_real_distribution<double> randdouble(-1.0, 1.0);

//Type aliases for better readability (pseudonyms for data storage types)
using Matrix = std::vector<std::vector<double>>;
using Filter = std::vector<Matrix>;
using Filters = std::vector<Filter>;
using Image = std::vector<Matrix>;

//layers after pooling
const int pool_after_conv_slot = 2;
const int second_pool_after_conv_slot = 4;

//size of the actual scanning matrix (kernel) for the convolution operation
int kernel_size_y = 3;
int kernel_size_x = 3;

//input image dimensions (height and width)
int image_y_dim = 128;
int image_x_dim = 128;

int final_class_number = 20;

//class definition for the Convolutional Neural Network (CNN)
class CNN {
  /**ordinarily, some data would be private, but for the sake of this educational example,
  we will make everything public for easier access and understanding.**/
  public:
  std::vector<Filters> filters;
  
  //bias, input map, temporary map for pooling, and number of kernels per layer initialization
  std::vector<std::vector<double>> biases;
  std::vector<int> number_of_kernels_or_whatever_per_layer = {16, 36, 42, 58, 80, 100};
  std::vector<std::vector<Matrix>> darn_input_maps;
  std::vector<std::vector<Matrix>> temporary_map_for_pooling;
  std::vector<std::vector<double>> class_weighty_things;
  std::vector<double> class_biasy_things;
  std::vector<Matrix> photo_vectors; //input image data

  //inline function for the Rectified Linear Unit (ReLU) activation function for nonlinear transformation
  inline double ReLU (double multipliedValue) {
    return (multipliedValue > 0) ? multipliedValue : 0.0;
  }

  std::vector<double> softmax (const std::vector<double> &input_vector) {
    if (input_vector.empty()) {
      return {};
    }
    
    std::vector<double> output_vector(input_vector.size());
    double max_value = *std::max_element(input_vector.begin(), input_vector.end());
    double sum_exp = 0.0;
    for (const auto &value : input_vector) {
      sum_exp += std::exp(value - max_value);
    }
    for (int i = 0; i < input_vector.size(); ++i) {
      output_vector[i] = std::exp(input_vector[i] - max_value) / sum_exp;
    }

    return output_vector;
  }

  //STILL IN PROGRESS!
  Image create_vector_to_input_from_this_darn_picturey_thing () {
    std::string filename;
    std::cout << "Enter the filename of your image: ";
    std::getline(std::cin, filename);
    cv::Mat decoded = cv::imread(filename, cv::IMREAD_COLOR);
    if (decoded.empty()) {
      std::cerr << "Error: Could not open or find the image." << std::endl;
      return {};

    }
    return photo_vectors;
  }
  //WORK HERE
  
  std::vector<double> classify (const std::vector<Matrix> &input_maps, const std::vector<std::vector<double>>& class_weights, const std::vector<double>& class_biases) {
    if (input_maps.empty()) {
      return {};
    }
    
    std::vector<double> intermediate_vector(input_maps.size(), 0.0);
    std::vector<double> output_vector(final_class_number, 0.0);

    for (int map_count = 0; map_count < input_maps.size(); map_count++) {
      double sum = 0.0;
      for(int row = 0; row < input_maps[map_count].size(); row++) {
        for (int col = 0; col < input_maps[map_count][row].size(); col++) {
          sum += input_maps[map_count][row][col];
        }
      }
      intermediate_vector[map_count] = sum/(input_maps[map_count].size() * input_maps[map_count][0].size());
    }
    
    for (int class_index = 0; class_index < final_class_number; class_index++) {
      double class_sum = class_biases[class_index];
      for (int averaged_map = 0; averaged_map < intermediate_vector.size(); averaged_map++) {
        class_sum += class_weights[class_index][averaged_map] * intermediate_vector[averaged_map];
      }
      output_vector[class_index] = class_sum;
    }

    return softmax(output_vector);
  }

  //main function for performing convolution operation with kernels (filters) on input maps
  Image multiplyKernels (int layer_number, const Filters &thingamabob, const Image &input_maps, const std::vector<std::vector<double>> &biases) {
    if (input_maps.empty() || thingamabob.empty()) {
      return {};
    }
    else {
      //for(int layer_number = 0; layer_number < thingamabob.size(); layer_number++) {
        for (int no_of_filter = 0; no_of_filter < thingamabob/**[layer_number]**/.size(); no_of_filter++) {
          int output_width = input_maps[0][0].size() - kernel_size_x + 1;
          int output_height = input_maps[0].size() - kernel_size_y + 1;
          for (int pixel_y = 0; pixel_y < output_height; pixel_y++) {
            for (int pixel_x = 0; pixel_x < output_width; pixel_x++) {
              double sum = biases[layer_number][no_of_filter];
              for (int no_of_channel = 0; no_of_channel < thingamabob[no_of_filter].size(); no_of_channel++) {
                for (int row = 0; row < kernel_size_y; row++) {
                  for (int col = 0; col < kernel_size_x; col++) {
                    
                    sum += thingamabob[no_of_filter][no_of_channel][row][col] * input_maps[no_of_channel][pixel_y + row][pixel_x + col];
                  } //work on putting the darn thing in the matrix
                }
              }
              sum = ReLU(sum);
              
              if (layer_number + 1 == second_pool_after_conv_slot) {
                temporary_map_for_pooling[1][no_of_filter][pixel_y][pixel_x] = sum;
              } else if (layer_number + 1 == pool_after_conv_slot) {
                temporary_map_for_pooling[0][no_of_filter][pixel_y][pixel_x] = sum;
              } else {
                darn_input_maps[layer_number + 1][no_of_filter][pixel_y][pixel_x] = sum;
              }
            }
          }
        }
      //}
        return darn_input_maps[layer_number + 1];
    }    
  }

  //please excuse the name of this function, I was frustrated when I wrote it and wanted to express my feelings about the pooling operation.
  /**std::vector<**/std::vector<Matrix>/**>*/ max_pool_this_darn_thing (int layer_number, const std::vector<std::vector<Matrix>> &input_maps) {
    if (input_maps.empty()) {
      return {};
    }
    else {
      int output_width = input_maps[layer_number][0][0].size() / 2;
      int output_height = input_maps[layer_number][0].size() / 2;
      std::vector<std::vector<Matrix>> pooled_maps = input_maps;
      for (int no_of_filter = 0; no_of_filter < input_maps[layer_number].size(); no_of_filter++) {
        pooled_maps[layer_number][no_of_filter].resize(output_height);
        for (int row = 0; row < output_height; row++) {
          pooled_maps[layer_number][no_of_filter][row].resize(output_width);
          for (int col = 0; col < output_width; col++) {
            double max_val = input_maps[layer_number][no_of_filter][row * 2][col * 2];
            max_val = std::max(max_val, input_maps[layer_number][no_of_filter][row * 2][col * 2 + 1]);
            max_val = std::max(max_val, input_maps[layer_number][no_of_filter][row * 2 + 1][col * 2]);
            max_val = std::max(max_val, input_maps[layer_number][no_of_filter][row * 2 + 1][col * 2 + 1]);
            pooled_maps[layer_number][no_of_filter][row][col] = max_val;
          }
        }
      }
      return pooled_maps[layer_number];
    }
  }

  //constructor for the CNN class, initializing filters, biases, input maps, and temporary maps for pooling
  CNN () {
    filters.resize(number_of_kernels_or_whatever_per_layer.size());
    biases.resize(number_of_kernels_or_whatever_per_layer.size());
    darn_input_maps.resize(number_of_kernels_or_whatever_per_layer.size() + 1);
    temporary_map_for_pooling.resize(2);
    for (int layer = 0; layer < 2; layer++) {
      temporary_map_for_pooling[layer].resize(number_of_kernels_or_whatever_per_layer[(layer == 1) ? second_pool_after_conv_slot - 1 : pool_after_conv_slot - 1]);
      for (int filter = 0; filter < temporary_map_for_pooling[layer].size(); filter++) {
        temporary_map_for_pooling[layer][filter].resize((layer == 0) ? 124 : 58);
        for (int row = 0; row < temporary_map_for_pooling[layer][filter].size(); row++) {
          temporary_map_for_pooling[layer][filter][row].resize((layer == 0) ? 124 : 58);
          for (int col = 0; col < temporary_map_for_pooling[layer][filter][row].size(); col++) {
            temporary_map_for_pooling[layer][filter][row][col] = 0.0;
          }
        }
      }
    }

    //input map sizing
    int dimension;
    for (int layer = 0; layer < number_of_kernels_or_whatever_per_layer.size() + 1; layer++) {
      darn_input_maps[layer].resize((layer == 0) ? 3 : number_of_kernels_or_whatever_per_layer[layer - 1]);
      switch (layer) {
        case 0:
          dimension = image_x_dim;
          break;
        case pool_after_conv_slot:
          dimension = (darn_input_maps[layer - 1][0].size() - kernel_size_x + 1) / 2;
          break;
        case second_pool_after_conv_slot:
          dimension = (darn_input_maps[layer - 1][0].size() - kernel_size_x + 1) / 2;
          break;
        default:
          dimension = darn_input_maps[layer - 1][0].size() - kernel_size_x + 1;
          break;
      }
      for (int filter = 0; filter < (layer == 0 ? 3 : number_of_kernels_or_whatever_per_layer[layer - 1]); filter++) {
        darn_input_maps[layer][filter].resize(dimension);
        for (int row = 0; row < dimension; row++) {
          darn_input_maps[layer][filter][row].resize(dimension);
          for (int col = 0; col < dimension; col++) {
            darn_input_maps[layer][filter][row][col] = 0.0;
          }
        }
      }
    }

    //bias sizing
    for (int layer = 0; layer < number_of_kernels_or_whatever_per_layer.size(); layer++) {
      biases[layer].resize(number_of_kernels_or_whatever_per_layer[layer]);
      for (int num_filter = 0; num_filter < number_of_kernels_or_whatever_per_layer[layer]; num_filter++) {
        biases[layer][num_filter] = randdouble(rng);
      }
    }
    
    //random initialization of weights
    for (int ft = 0; ft <  number_of_kernels_or_whatever_per_layer.size(); ft++) {
      filters[ft].resize(number_of_kernels_or_whatever_per_layer[ft]);
      for (int number_of_filters = 0; number_of_filters < number_of_kernels_or_whatever_per_layer[ft]; number_of_filters++) {
        filters[ft][number_of_filters].resize((ft == 0) ? 3 : number_of_kernels_or_whatever_per_layer[ft - 1]);
        for (int num_of_input_maps_per_filter_aka_channels = 0; num_of_input_maps_per_filter_aka_channels < ((ft == 0) ? 3 : number_of_kernels_or_whatever_per_layer[ft - 1]); num_of_input_maps_per_filter_aka_channels++) {
          filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels].resize(kernel_size_x);
          for (int row = 0; row < kernel_size_x; row++){
            filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels][row].resize(kernel_size_y);
            for (int col = 0; col < kernel_size_y; col++) {
              filters[ft][number_of_filters][num_of_input_maps_per_filter_aka_channels][row][col] = randdouble(rng);
            }
          }
        }
      }
    }
    //HERE
    //random initialization of classifier weights and biases
    
    class_weighty_things.resize(final_class_number);
    class_biasy_things.resize(final_class_number);

    for (int class_index = 0; class_index < final_class_number; class_index++) {
      class_weighty_things[class_index].resize(darn_input_maps.back().size());
      class_biasy_things[class_index] = randdouble(rng);
      for (int feature_index = 0; feature_index < darn_input_maps.back().size(); feature_index++) {
        class_weighty_things[class_index][feature_index] = randdouble(rng);
      }
    }

  }
};

//finally, the main function to run the CNN
int main() {
  CNN cnn;
  for (int layer = 0; layer < cnn.filters.size(); layer++) {
    cnn.multiplyKernels(layer, cnn.filters[layer], (layer == 0) ? cnn.photo_vectors : cnn.darn_input_maps[layer - 1], cnn.biases);
    if (layer == pool_after_conv_slot - 1 || layer == second_pool_after_conv_slot - 1) {
      cnn.darn_input_maps[layer + 1] = cnn.max_pool_this_darn_thing(((layer == 1) ? 0 :  1), cnn.temporary_map_for_pooling);
    }
  }
  
  std::vector<double> predictions = cnn.classify(cnn.darn_input_maps.back(), cnn.class_weighty_things, cnn.class_biasy_things);
  std::cout << "Predictions: ";
  for (const auto &probability : predictions) {
    std::cout << probability << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
