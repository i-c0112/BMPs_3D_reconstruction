#include <fstream>
#include <stdexcept>
#include "struct_pixel.h"

const char* BIN_FILENAME = "parsed.bindata";

struct bad_read : public std::runtime_error
{
    bad_read(const char* msg) : std::runtime_error(msg) {}
};

bool bmp2binary_open_for_write(std::fstream &fd, bool clean=false)
{
    fd.close();
    fd.open(BIN_FILENAME, (clean? std::ios::binary | std::ios::out | std::ios::trunc :
                                              std::ios::binary | std::ios::out | std::ios::app) ) ;

    return fd.is_open();
}
bool bmp2binary_open_for_read(std::fstream &fd)
{
    fd.close();
    fd.open(BIN_FILENAME, std::ios::binary | std::ios::in);
    return fd.is_open();
}

bool bmp2binary_write(std::fstream & fd, const util_pixel &px)
{
    if (!fd.is_open())
        return false;

    fd.write((char *)&px, sizeof(util_pixel));
    return true;
}

bool bmp2binary_read(std::fstream & fd, util_pixel &pxOut)
{
    if (!fd.is_open())
        throw bad_read("bad fstream read operation: not associated!\n");

	//! beware always check eof after read and also check for fail or error
    if (!(fd.read((char *)&pxOut, sizeof(util_pixel))) || fd.eof())
		return false;

	return true;
}
