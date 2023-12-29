#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"


namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
      void fill(int x, int y, int w, int h,rgb_value r,rgb_value g,rgb_value b);
      void clear_image_if_any();
      void open();
      void blank();
      void save();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::string input;


  };
}
#endif