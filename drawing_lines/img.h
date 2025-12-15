#pragma once
#include "BitmapPlusPlus.hpp"


class Img
{
public:
    static void draw_line(bmp::Bitmap *bmp, int end_x, int end_y, int x0, int y0, const bmp::Pixel *px);
};
