#pragma once
#include <tuple>
#include <iostream>


template<size_t N, typename Tuple>
struct TuplePrinter {
    static void print(std::ostream& os, Tuple const& t) {
        TuplePrinter<N - 1, Tuple>::print(os, t);
        os << "," << std::get<N>(t);
    }
};

template<typename Tuple>
struct TuplePrinter<0, Tuple> {
    static void print(std::ostream& os, Tuple const& t) {
        os << std::get<0>(t);
    }
};

template<typename... Args>
std::ostream& operator<<(std::ostream& os, std::tuple<Args...> const& t) {
    os << "(";
    TuplePrinter<sizeof...(Args) - 1, std::tuple<Args...>>::print(os, t);
    os << ")";
    return os;
}
