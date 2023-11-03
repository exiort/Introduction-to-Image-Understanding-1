#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
using ceng391::Image;

typedef unsigned char uchar;
int main(int /*argc*/, char** /*argv*/)
{
        Image* img = new Image(320,240,-1, 1);
        uchar value = 199;
        uchar* values = new uchar[3]{255, 0, 255};

        img->set_grayscale(value);
        value = 50;
        img->set_rect_grayscale(50,50,100,100,value);
        img->write_pnm("/tmp/first");
        img->load_pnm("/tmp/first.pgm");
        img->to_rgb();
        img->write_pnm("/tmp/second");
        img->set_rect_rgb(100,20,30,50,values);
        img->write_pnm("/tmp/third");

        delete[] values;
        delete img;
        
        EXIT_SUCCESS;
}
/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:

