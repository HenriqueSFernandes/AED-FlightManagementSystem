#include "Color.hpp"

namespace prog {
    //Default constructor. By default, the color should correspond to black, i.e., (0, 0, 0).
    Color::Color() {
        rgb_value zero = 0;
        r = zero;
        g = zero;
        b = zero;

    }

    //Copy constructor.
    Color::Color(const Color &other) {
        r = other.red();
        g = other.green();
        b = other.blue();

    }

    //Constructor using supplied (r, g, b) values.
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        r = red;
        g = green;
        b = blue;

    }

    //Get values for individual RGB color channels.
    rgb_value Color::red() const {

        return r;
    }

    rgb_value Color::green() const {
        return g;
    }

    rgb_value Color::blue() const {
        return b;
    }


    rgb_value &Color::red() {
        return r;
    }

    rgb_value &Color::green() {
        return g;
    }

    rgb_value &Color::blue() {
        return b;
    }

    bool Color::operator<(const Color &other) const { //This function is used in xpm2 to order map
        if (r < other.r) {
            return true;
        } else if (r > other.r) {
            return false;
        } else if (g < other.g) {
            return true;
        } else if (g > other.g) {
            return false;
        } else {
            return b < other.b;
        }
    }

}