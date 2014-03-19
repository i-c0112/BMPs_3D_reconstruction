#ifndef BMP2CSV_H_INCLUDED

const char CSV_FILENAME[] = "parsed.csv";

#define BMP2CSV_H_INCLUDED

#include <cstdio>
#include "struct_pixel.h"

bool bmp2csv_write(const util_pixel *pPx, bool clean = false)
{
    FILE *fd = fopen(CSV_FILENAME, (clean? "w": "a"));
    if (!fd)
    {
        fprintf(stderr, "Failed to open %s!\n", CSV_FILENAME);
        fclose(fd);
        return false;
    }

    if (fprintf(fd, "%d,%d,%d,%f,%f,%f\n", pPx->x, pPx->y, pPx->z, pPx->r, pPx->g, pPx->b) < 0)
    {
        fprintf(stderr, "Failed to write to %s!\n", CSV_FILENAME);
        fclose(fd);
        return false;
    }
    fclose(fd);
    return true;
}

FILE* bmp2csv_read(util_pixel* pPx, FILE *fd = nullptr)
{
    if (!fd)
    {
        fd = fopen(CSV_FILENAME, "r");
        if (!fd)
        {
            fprintf(stderr, "Failed to open %s!\n", CSV_FILENAME);
            return nullptr;
        }
    }

    constexpr int arg_cnt = 6;
    if (fscanf(fd, "%d,%d,%d,%f,%f,%f\n", &(pPx->x), &(pPx->y), &(pPx->z), &(pPx->r), &(pPx->g), &(pPx->b)) < arg_cnt)
    {
        /// should throw exception here because the lacking of information of what is going to do here
        fprintf(stderr, "Failed to read from %s!\n", CSV_FILENAME);
    }
    return fd;
}

#endif // BMP2CSV_H_INCLUDED
