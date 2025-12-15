#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


// int float....
template <typename T>
struct serializer {
    static void apply(const T &obj, std::ostream &os) {
        // const uint8_t *ptr = reinterpret_cast<const uint8_t *>(&obj); // адрес объекта преобразует в указатель на массив байтов
        // const std::ostream_iterator<uint8_t> oi(os);
        //
        // std::copy(ptr, ptr + sizeof(T), oi); // копирование всех байтов объекта в поток
        os.write(reinterpret_cast<const char*>(&obj), sizeof(T));
    }
};

// string
template <>
struct serializer<std::string>
{
    static void apply(const std::string &obj, std::ostream &os) {
        const size_t len = obj.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(obj.data(), len);
    }
};

template <typename T>
void serialize(const T &obj, std::ostream &os)
{
    serializer<T>::apply(obj, os);
}

// vector
template <typename T>
struct serializer<std::vector<T>>
{
    static void apply(const std::vector<T> &obj, std::ostream &os) {
        const size_t len = obj.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        for (const auto &v : obj)
        {
            serialize(v, os);
        }
    }
};

// map
template <typename T1, typename T2>
struct serializer<std::map<T1, T2>>
{
    static void apply(const std::map<T1, T2> &obj, std::ostream &os)
    {
        const size_t len = obj.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        for (const auto &p : obj)
        {
            serialize(p.first, os);
            serialize(p.second, os);
        }
    }
};


// int float....
template <typename T>
struct deserializer {
    static void apply(T &val, std::istream &is) {
        // uint8_t *ptr = reinterpret_cast<uint8_t*>(&val);
        // const std::istream_iterator<uint8_t> ii(is);
        //
        // std::copy_n(ii, sizeof(T), ptr);
        is.read(reinterpret_cast<char*>(&val), sizeof(T));
    }
};

// string
template <>
struct deserializer<std::string>
{
    static void apply(std::string &obj, std::istream &is) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        obj.resize(len);
        is.read(&obj[0], len);
    }
};

template <typename T>
void deserialize(T &obj, std::istream &is)
{
    return deserializer<T>::apply(obj, is);
}

// vector
template <typename T>
struct deserializer<std::vector<T>>
{
    static void apply(std::vector<T> &obj, std::istream &is) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        obj.resize(len);
        for (auto &v : obj)
        {
            deserialize(v, is);
        }
    }
};

// map
template <typename T1, typename T2>
struct deserializer<std::map<T1, T2>>
{
    static void apply(std::map<T1, T2> &obj, std::istream &is)
    {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        obj.clear();
        for (size_t i = 0; i < len; i++)
        {
            T1 key;
            deserialize(key, is);
            T2 val;
            deserialize(val, is);
            obj.insert(std::make_pair(key, val));
        }
    }
};
