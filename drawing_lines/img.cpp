#include "img.h"


void Img::draw_line(bmp::Bitmap *bmp, const int end_x, const int end_y, const int x0, const int y0, const bmp::Pixel *px)
{
    const int w = bmp->width();
    const int h = bmp->height();
    const int dx = abs(end_x - x0);
    const int dy = abs(end_y - y0);
    int error = dx - dy;
    int dir_x = 0, dir_y = 0;

    if (x0 < end_x)
        dir_x = 1;
    else
        dir_x = -1;

    if (y0 < end_y)
        dir_y = 1;
    else
        dir_y = -1;


    int x = x0, y = y0;
    while (true)
    {
        if (x >= 0 && x < w && y >= 0 && y < h)
            bmp->set(x, y, *px);

        if (x == end_x && y == end_y)
            break;

        const int e2 = 2 * error;
        if (e2 > -dy) {
            error -= dy;
            x += dir_x;
        }
        if (e2 < dx) {
            error += dx;
            y += dir_y;
        }
    }
}
