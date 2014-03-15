#ifndef STRUCT_PIXEL_H_INCLUDED
#define STRUCT_PIXEL_H_INCLUDED

struct util_pixel
{
    int x;
    int y;
    int z;

    float r;
    float g;
    float b;
};

inline float rgb_b2f(unsigned char b)
{
    return 1.0 * b / 256.0f;
}

#endif // STRUCT_PIXEL_H_INCLUDED
