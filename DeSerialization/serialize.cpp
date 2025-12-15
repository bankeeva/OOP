#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "serialize.h"

using namespace std;

int main()
{
    ofstream ofs("test.ser", ofstream::out | ofstream::binary);

    char hello[7] = "hello!";
    int boo[3] = {1, 2, 3};

    //
    string s = "hello world";
    serialize(s, ofs);

    vector<int> vec_num = {10, 20, 30, 40};
    serialize(vec_num, ofs);

    vector<string> vec_string = {"hi", "mom"};
    serialize(vec_string, ofs);

    map<string, int> mp = {{"one", 1}, {"two", 2}, {"three", 3}};
    serialize(mp, ofs);
    //

    serialize(hello, ofs);
    serialize(boo, ofs);

    char hello2[7];
    int boo2[3];

    ofs.close();

    ifstream ifs("test.ser", ifstream::in | ofstream::binary);
    ifs >> noskipws;

    //
    string s2;
    deserialize(s2, ifs);

    vector<int> vec2_num;
    deserialize(vec2_num, ifs);

    vector<string> vec2_string;
    deserialize(vec2_string, ifs);

    map<string, int> mp2;
    deserialize(mp2, ifs);
    //

    deserialize(hello2, ifs);
    deserialize(boo2, ifs);

    if (equal(hello, hello + 7, hello2))
        cout << "Hello OK!" << endl;

    if (equal(boo, boo + 3, boo2))
        cout << "Boo OK!" << endl;

    //
    if (s == s2)
        cout << "String OK!" << endl;

    if (vec_num == vec2_num)
        cout << "Vector_num OK!" << endl;

    if (vec_string == vec2_string)
        cout << "Vector_string OK!" << endl;

    if (mp == mp2)
        cout << "Map OK!" << endl;
    //

    return 0;
}
