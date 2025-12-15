#include "BitmapPlusPlus.hpp"
#include "img.h"
#include <iostream>
#include <fstream>
#include <string>


int main()
{
    std::string in_file;
    std::string in_bmp, out_bmp;
    int start[2], end[2], r, g, b;
    bmp::Bitmap bmp;
    bmp::Pixel px;

    std::cin >> in_file;
    std::ifstream file(in_file);
    if (!file.is_open())
    {
        std::cerr << "Can't open file" << std::endl;
        return 0;
    }

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file >> in_bmp;
        file >> start[0] >> start[1];
        file >> end[0] >> end[1];
        file >> r >> g >> b;
        file >> out_bmp;
    } catch (const std::ios_base::failure& e)
    {
        std::cout << "Ошибка чтения файла: " << e.what() << std::endl;
        return 0;
    }
    file.close();

    try
    {
        bmp.load(in_bmp);
    } catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 0;
    }

    px.r = r;
    px.g = g;
    px.b = b;

    if (px.r > 255 || px.g > 255 ||
        px.b > 255 || px.r < 0 ||
        px.g < 0 || px.b < 0)
    {
        std::cout << "Значение цвета выходит за диапазон RGB, поэтому будет использоваться стандартный - черный" << std::endl;
        px = {0, 0, 0};
    }

    bmp::Bitmap o_bmp = bmp;

    Img::draw_line(&o_bmp, end[0], end[1], start[0], start[1], &px);

    try
    {
        o_bmp.save(out_bmp);
        std::cout << "Начерченная линия находится в файле " << out_bmp << std::endl;
    } catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
