#ifndef STRUCT_PIXEL_H_INCLUDED
#define STRUCT_PIXEL_H_INCLUDED

#include <cstdint>

inline float rgb_b2f(unsigned char b)
{
    return 1.0 * b / 256.0f;
}

struct util_pixel
{
    int x;
    int y;
    int z;

    float r;
    float g;
    float b;
};

struct util_pixel_cross_platform_storage
{
    int16_t x;
    int16_t y;
    int16_t z;
    int8_t br;
    int8_t bg;
    int8_t bb;

    operator util_pixel() const
    {
        util_pixel px;
        px.x = x; px.y = y; px.z = z;
        px.r = rgb_b2f(br); px.g = rgb_b2f(bg); px.b = rgb_b2f(bb);
        return std::move(px);
    }
};

#endif // STRUCT_PIXEL_H_INCLUDED
