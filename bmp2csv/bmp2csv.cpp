constexpr int NUM_OF_FILES_TO_READ = 400;

#include <iostream>
#include <deque>
#include <stdexcept>
#include "bitmap_image.hpp"
#include "bmp2csv.h"

using namespace std;

class BAD_OP : public runtime_error
{
public:
    BAD_OP() : runtime_error("Bad result on I/O operation!\n") {}
};

void read_single_bmp(int idx, bool clean = false)
{
    char filename_to_read[16];
    sprintf(filename_to_read, "Sample/%i.bmp", idx);

    bitmap_image bmp(filename_to_read);

    unsigned int h = bmp.height();
    unsigned int w = bmp.width();

    /// !!!!!!!!!!!!!!!!WEIRD!!!!!!!!!!!
    /// height need to minus 2 or there will be white lines at the bottom of the pic!
    for (unsigned int y = 0; y < h-2; ++y)
    {
        for (unsigned int x = 0; x < w; ++x)
        {
            unsigned char uR, uG, uB;
            bmp.get_pixel(x, y, uR, uG, uB);

            if (uR < 128 && uG < 128 && uB < 128)
                continue;

            util_pixel px;
            /// this should be adjusted by the opengl program.
            /// px.x = x - 484; px.y = -(y - 246); px.z = idx * -2 + 400;
            px.x = x; px.y = y; px.z = idx;

            px.r = rgb_b2f(uR); px.g = rgb_b2f(uG); px.b = rgb_b2f(uB);
            bool res = bmp2csv_write(&px, clean);
            if (!res)
                throw BAD_OP();
        }
    }
}
inline void read_bmps(int total)
{
    bool clean = true;
    for (int idx = 1; idx <= total; ++idx)
    {
        read_single_bmp(idx, clean);
        clean = false;
    }
}

int main()
{
    try
    {
        read_bmps(NUM_OF_FILES_TO_READ);
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
