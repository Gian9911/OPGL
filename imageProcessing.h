#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "Libraries/include/stb/stb_image.h"
#include "Libraries/include/stb/stb_image_write.h"
#include <cmath>
#include <iostream>
#include <vector>

struct Color {
  unsigned char r, g, b;
};
struct Gray {
  unsigned char gray;
};
enum type_padding { zero, pixel_replication, pixel_mirroring };

class ImageProcessing {
  /*
    int width, height, channels;
    unsigned char *diffuse_data = stbi_load("textures/stone_wall_diffuse.jpeg", &width, &height, &channels, 3);
    // Convert the diffuse map to Color struct
    std::vector<Color> diffuse_map(width * height);
    for (int i = 0; i < width * height; i++) {
      diffuse_map[i].r = diffuse_data[i * 3];
      diffuse_map[i].g = diffuse_data[i * 3 + 1];
      diffuse_map[i].b = diffuse_data[i * 3 + 2];
    }
    stbi_image_free(diffuse_data); // Free the stb_image data
    double strength = 1.0;
    // Compute the normal map using the Sobel filter
    std::vector<Color> normal_map(width * height);
    std::vector<Gray> gray_img = rgbToGray(diffuse_map, width, height, channels);
    compute_normal_map(gray_img.data(), width, height, strength, normal_map.data());
    if (!stbi_write_png("gray.png", width, height, 1, gray_img.data(), width)) {
      std::cout << "Failed to write the image." << std::endl;
      return 1;
    }
    // Write the normal map using stb_image_write (replace 'normal_map_path' with your output path)
    if (!stbi_write_png("normal_map.png", width, height, 3, normal_map.data(), width * 3)) {
      std::cout << "Failed to write the image." << std::endl;
      return 1;
    }
  */
private:
  std::vector<Gray> rgbToGray(unsigned char *diffuse_data, int width, int height);
  std::vector<Gray> apply_padding_to_image(std::vector<Gray> img, const int kernel_size, type_padding padding,int height,int width);
  // Function to compute the normal map
public:
  ImageProcessing();
  int compute_normal_map(std::string diffusePath, double strength);
  int compute_specular_map(std::string diffusePath);
  std::vector<Gray> edge_detection(std::vector<Gray> grey_map,int height,int width);
  std::vector<Gray> inversion_value(std::vector<Gray> grey_map,int height,int width);
};

#endif