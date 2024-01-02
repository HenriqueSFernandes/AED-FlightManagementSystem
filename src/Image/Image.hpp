#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__

#include "Color.hpp"
#include <vector>

namespace prog {
    class Image {
    private:
        // TODO: define private fields for image state
        int w;
        int h;
        std::vector<std::vector<Color>> pixels;            //Initializes vector with size w, filled with vector of colors of size h
    public:
        Image(int w, int h, const Color &fill = {255, 255, 255});

        ~Image();

        int width() const;

        int height() const;

        Color &at(int x, int y);

        const Color &at(int x, int y) const;
    };
}
#endif