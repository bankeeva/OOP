#include <gtest/gtest.h>
#include <fstream>
#include <algorithm>
#include "../serialize.h"
#include <vector>
#include <map>
#include <string>

// строки
TEST(SimpleSerializationTest, String) {
    const std::string filename = "string_test.ser";

    std::string s = "hello world";
    {
        std::ofstream ofs(filename, std::ios::binary);
        serialize(s, ofs);
    }

    std::string s2;
    {
        std::ifstream ifs(filename, std::ios::binary);
        deserialize(s2, ifs);
    }

    EXPECT_EQ(s, s2);
}

// vector<int>
TEST(SimpleSerializationTest, VectorInt) {
    const std::string filename = "vector_int_test.ser";

    std::vector<int> vec_num = {10, 20, 30, 40};
    {
        std::ofstream ofs(filename, std::ios::binary);
        serialize(vec_num, ofs);
    }

    std::vector<int> vec2_num;
    {
        std::ifstream ifs(filename, std::ios::binary);
        deserialize(vec2_num, ifs);
    }

    EXPECT_EQ(vec_num, vec2_num);
}

// vector<string>
TEST(SimpleSerializationTest, VectorString) {
    const std::string filename = "vector_string_test.ser";

    std::vector<std::string> vec_string = {"hi", "mom"};
    {
        std::ofstream ofs(filename, std::ios::binary);
        serialize(vec_string, ofs);
    }

    std::vector<std::string> vec2_string;
    {
        std::ifstream ifs(filename, std::ios::binary);
        deserialize(vec2_string, ifs);
    }

    EXPECT_EQ(vec_string, vec2_string);
}

// map<string,int>
TEST(SimpleSerializationTest, MapStringInt) {
    const std::string filename = "map_test.ser";

    std::map<std::string, int> mp = {{"one",1}, {"two",2}, {"three",3}};
    {
        std::ofstream ofs(filename, std::ios::binary);
        serialize(mp, ofs);
    }

    std::map<std::string,int> mp2;
    {
        std::ifstream ifs(filename, std::ios::binary);
        deserialize(mp2, ifs);
    }

    EXPECT_EQ(mp, mp2);
}

// массив char
TEST(SimpleSerializationTest, CArrayChar) {
    const std::string filename = "carray_char_test.ser";

    char hello[7] = "hello!";
    char hello2[7]{};

    {
        std::ofstream ofs(filename, std::ios::binary);
        for (char c : hello) serialize(c, ofs);
    }

    {
        std::ifstream ifs(filename, std::ios::binary);
        for (auto &c : hello2) deserialize(c, ifs);
    }

    EXPECT_TRUE(std::equal(hello, hello + 7, hello2));
}

// массив int
TEST(SimpleSerializationTest, CArrayInt) {
    const std::string filename = "carray_int_test.ser";

    int boo[3] = {1, 2, 3};
    int boo2[3]{};

    {
        std::ofstream ofs(filename, std::ios::binary);
        for (int x : boo) serialize(x, ofs);
    }

    {
        std::ifstream ifs(filename, std::ios::binary);
        for (auto &x : boo2) deserialize(x, ifs);
    }

    EXPECT_TRUE(std::equal(boo, boo + 3, boo2));
}

// структура
struct Person {
    std::string name;
    int age;

    bool operator==(const Person &other) const {
        return name == other.name && age == other.age;
    }
};

inline void serialize(const Person &p, std::ostream &os) {
    serialize(p.name, os);
    serialize(p.age, os);
}

inline void deserialize(Person &p, std::istream &is) {
    deserialize(p.name, is);
    deserialize(p.age, is);
}

TEST(SimpleSerializationTest, StructPerson) {
    const std::string filename = "person_test.ser";

    Person p1{"Alice", 30};
    Person p2;

    {
        std::ofstream ofs(filename, std::ios::binary);
        serialize(p1, ofs);
    }

    {
        std::ifstream ifs(filename, std::ios::binary);
        deserialize(p2, ifs);
    }

    EXPECT_EQ(p1, p2);
}
