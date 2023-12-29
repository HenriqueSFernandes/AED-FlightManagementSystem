#include <iostream>
#include <fstream>
#include <algorithm>
#include "Script.hpp"
#include "PNG.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }


    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        image = loadFromPNG(input);
        cout<<image->width();
    }


    void Script::save() {
        // Save current image to PNG file.
        string filename;
        saveToPNG(input, image);
    }

    void Script::fill(int x, int y, int w, int h,rgb_value r,rgb_value g,rgb_value b){
        //Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h


        int x_ = image->width();
        int y_ = image->height();
        for(int i = 0; i < x_; i++){
            for (int j=0; j < y_; j++){
                if((i>=x and i<x+w) and (j>=y and j<y+h)  ){    //Condition for it to be in the rectangle
                    image->at(i,j).red()=r;
                    image->at(i,j).green()=g;
                    image->at(i,j).blue()=b;

                }
            }
        }
    }


 
void window_calculator(vector<int> &helper,int i, int j, int left, int right, int up, int down,int n){ //gets the new values for the window taking into consideration the image limits
    int displacement =(n-1)/2;
    int newleft,newright,newup,newdown;
    newleft=i-displacement;
    if(newleft<left){newleft=left;}
    newright=i+displacement;
    if(newright>right){newright=right;}
    newup=j-displacement;
    if(newup<up){newup=up;}
    newdown=j+displacement;
    if(newdown>down){newdown=down;}
    helper[0]=newleft;
    helper[1]=newright;
    helper[2]=newup;
    helper[3]=newdown;

    }


 
}
