#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "Libraries/include/stb/stb_image.h"
#include "Libraries/include/stb/stb_image_write.h"
#include <cmath>
#include <iostream>
#include <vector>
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
struct Color {
  unsigned char r, g, b;
};
struct Gray {
  unsigned char gray;
};
// Function to compute the normal map
void compute_normal_map(const Gray *map, int width, int height, double strength, Color *normal_map) {
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      // Calculate gradients in the x and y directions
      int gx = (map[(y - 1) * width + (x + 1)].gray + 2 * map[y * width + (x + 1)].gray + map[(y + 1) * width + (x + 1)].gray) -
               (map[(y - 1) * width + (x - 1)].gray + 2 * map[y * width + (x - 1)].gray + map[(y + 1) * width + (x - 1)].gray);

      int gy = (map[(y + 1) * width + (x - 1)].gray + 2 * map[(y + 1) * width + x].gray + map[(y + 1) * width + (x + 1)].gray) -
               (map[(y - 1) * width + (x - 1)].gray + 2 * map[(y - 1) * width + x].gray + map[(y - 1) * width + (x + 1)].gray);

      // Calculate the normal vector
      double length = std::sqrt(gx * gx + gy * gy + 255 * 255); // 255 is the depth range (maximum intensity value) [gx,gy,255]
      double nx = -gx * strength / length;
      double ny = -gy * strength / length;
      double nz = 1.0;

      // Normalize the normal vector
      double norm = std::sqrt(nx * nx + ny * ny + nz * nz);
      nx /= norm;
      ny /= norm;
      nz /= norm;

      // Convert the normal vector to RGB values
      normal_map[y * width + x].r = static_cast<unsigned char>((nx + 1.0) * 0.5 * 255);
      normal_map[y * width + x].g = static_cast<unsigned char>((ny + 1.0) * 0.5 * 255);
      normal_map[y * width + x].b = static_cast<unsigned char>((nz + 1.0) * 0.5 * 255);
    }
  }
}
std::vector<Gray> rgbToGray(std::vector<Color> img, int width, int height, int channels) {
  std::vector<Gray> gray_img(width * height);
  int index_gray = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // 0.299 ∙ Red + 0.587 ∙ Green + 0.114 ∙ Blue
      int index = j + width * i;
      gray_img[index].gray = 0.299f * img[index].r + 0.587f * img[index].g + 0.114f * img[index].b;
    }
  }
  // std::cout << index_write << " out of " << widthImg * heightImg<<std::endl;
  return gray_img;
}
#endif