#pragma once
#include <sstream>
#include <tuple>
#include <vector>
#include <stdexcept>
#include "tuple_print.h"


class CSVError : public std::runtime_error {
public:
    CSVError(const std::string& m) : std::runtime_error(m) {}
};


struct CSVConfig {
    char col_delim = ',';
    char row_delim = '\n';
    char quote = '"';
};


template<typename... Args>
class CSVParser {
    std::istream& in;
    size_t skip_lines;
    CSVConfig cfg;


    class Iterator {
        std::istream* pin; // указатель на поток
        CSVConfig cfg;
        bool ended = false;
        std::tuple<Args...> row;
        size_t line_num = 0;

        std::vector<std::string> parse(const std::string& line) {
            std::vector<std::string> res;
            std::string cur;
            bool in_quote = false;

            for (char c : line) {
                if (c == cfg.quote) {
                    in_quote = !in_quote;
                }
                else if (c == cfg.col_delim && !in_quote) {
                    res.push_back(cur);
                    cur.clear();
                }
                else {
                    cur.push_back(c);
                }
            }
            res.push_back(cur);
            return res;
        }

        template<size_t I = 0>
        void convert(const std::vector<std::string>& cols) {
            if constexpr (I < sizeof...(Args)) {

                using T = typename std::tuple_element<I, std::tuple<Args...>>::type;

                std::istringstream ss(cols[I]);
                T val;
                ss >> val;

                if (ss.fail()) {
                    throw CSVError(
                        "Ошибка в строке " + std::to_string(line_num) +
                        ", колонка " + std::to_string(I) +
                        ": \"" + cols[I] + "\""
                    );
                }

                std::get<I>(row) = val;

                convert<I + 1>(cols);
            }
        }


    public:
        Iterator(std::istream* p, size_t skip_lines, CSVConfig cfg_)
            : pin(p), cfg(cfg_)
        {
            std::string tmp;
            for (size_t i = 0; i < skip_lines; i++) {
                std::getline(*pin, tmp);
                line_num++;
            }

            ++(*this);
        }

        Iterator() : pin(nullptr), ended(true) {}

        bool operator!=(const Iterator& other) const {
            return ended != other.ended;
        }

        bool operator==(const Iterator& other) const {
            return ended == other.ended;
        }


        const std::tuple<Args...>& operator*() const { return row; }

        Iterator& operator++() {
            if (!pin || !*pin) { ended = true; return *this; }

            std::string line;
            if (!std::getline(*pin, line, cfg.row_delim)) {
                ended = true;
                return *this;
            }

            line_num++;

            auto cols = parse(line);
            if (cols.size() != sizeof...(Args))
                throw CSVError(
                    "Ошибка: неверное число колонок в строке " + std::to_string(line_num)
                );

            convert(cols);
            return *this;
        }
    };


public:
    CSVParser(std::istream& s, size_t sk = 0, CSVConfig c = {})
        : in(s), skip_lines(sk), cfg(c) {}

    Iterator begin() { return Iterator(&in, skip_lines, cfg); }
    Iterator end() { return Iterator(); }
};
