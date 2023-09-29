#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

void render() {
    const int width = 1024, height = 768;
    std::vector<Vec3f> framebuffer (width*height);

    // For each pixel, sets the G value as the pixel's height and the B value as its width. R is always zero.
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            framebuffer[j + i*width] = Vec3f(0, i / float(height), j / float(width));
        }      
    }

    std::ofstream file;
    file.open("./image.ppm", std::ofstream::out | std::ofstream::binary);

    file << "P6\n" << width << " " << height << "\n255\n"; // Specifying the type and dimensions of image to the .ppm file.

    // Makes it so the pixel values never go lower than 0 or higher than 1, then multiplies them by 255 before writing to file.
    for (size_t i = 0; i < width*height; ++i) { 
        for (size_t j = 0; j < 3; j++) {
            file << (char) (255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }

    file.close();
}

int main() {
    render();
    return 0;
}