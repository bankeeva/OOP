#include "BitmapPlusPlus.hpp"
#include <iostream>

int main() {
    const int width = 50;
    const int height = 50;

    bmp::Bitmap bmp(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bmp.set(x, y, bmp::Pixel(255, 255, 255));
        }
    }

    try {
        bmp.save("kitty.bmp");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при сохранении файла: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
