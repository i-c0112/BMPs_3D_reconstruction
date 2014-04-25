// configuration
#define CROSS_PLATFORM_STORAGE
const char *DIR = "Sample/";
const int file_count = 400;
const unsigned char threshold = 112;
// end of configuration

#include <iostream>
#include <sstream>
#include "bmp2binary.h"
#include "bitmap_image.hpp"

int main()
{
    std::fstream fd;
    bmp2binary_open_for_write(fd, true);

    std::stringstream ss;
    for (int i = 1; i <= file_count; ++i)
    {
        ss.str("");
        ss << (std::string)DIR;
        ss << i << std::string(".bmp");

        bitmap_image bmp(ss.str());
        unsigned int w = bmp.width();
        unsigned int h = bmp.height();
        unsigned char r,g,b;

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //! WEIRD: should -2 or they will be redundant lines
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for (unsigned int y = 0; y < h - 2; ++y)
        {
            for(unsigned int x = 0; x < w; ++x)
            {
                bmp.get_pixel(x, y, r, g, b);

                if (r < threshold || g < threshold || b < threshold)
                    continue;

#ifdef CROSS_PLATFORM_STORAGE
                util_pixel_cross_platform_storage px;
                px.x = (int16_t)x; px.y = (int16_t)y; px.z = (int16_t)i;
                px.br = (int8_t)r; px.bg = (int8_t)g; px.bb = (int8_t)b;
#else
                util_pixel px;
                px.x = x; px.y = y; px.z = i;
                px.r = rgb_b2f(r); px.g = rgb_b2f(g); px.b = rgb_b2f(b);
#endif

                if (!bmp2binary_write(fd, px))
                    return 1;
            }
        }
    }

    return 0;
}
