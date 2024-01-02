#include "Image.hpp"

namespace prog {
    //Constructor that creates image with width w, height h, and all pixels set to color fill
    Image::Image(int w, int h, const Color &fill) {
        this->w = w;
        this->h = h;
        for (int x = 0; x < w; x++) {
            std::vector<Color> height;
            pixels.push_back(height);     //Create empty column
            for (int y = 0; y < h; y++) {
                pixels[x].push_back(fill);  //Fill each column with the color fill
            }
        }
    }

    Image::~Image() {                  //Not used in our implementation
    }

    //Get function for width
    int Image::width() const {
        return w;
    }

    //Get function for height
    int Image::height() const {
        return h;
    }

    //Function that returns a mutable reference to the color object in a pixel
    Color &Image::at(int x, int y) {
        return pixels[x][y];
    }

    //Function that returns a read-only reference to the color object in a pixel
    const Color &Image::at(int x, int y) const {
        return pixels[x][y];
    }
}