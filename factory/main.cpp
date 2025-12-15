#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "object.h"
#include "object.cpp"


int main(int argc, char *argv[]) {
    std::string cur;

    std::fstream file;
    if (argc != 2) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return 1;
    }

    file.open(argv[1]);

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << argv[1] << std::endl;
        return 1;
    }

    while (getline(file, cur)) {
        std::vector<std::string> words;
        int ind = 0;

        while (ind < cur.size()) {
            std::string word;

            while (cur[ind] != ' ' and cur[ind] != '\n' and ind < cur.size()) {
                word += cur[ind];
                ind++;
            }
            if (cur[ind] == ' ' or cur[ind] == '\n') ind++;
            words.push_back(word);
        }

        std::unique_ptr<Shape> shape(ShapeFactory::createShape(words));
        if (shape)
        {
            shape->draw();
        }
    }

    return 0;
}