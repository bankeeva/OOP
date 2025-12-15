#include <gtest/gtest.h>
#include <sstream>
#include "../parser.h"
#include "../tuple_print.h"


// Проверяет базовый разбор двух строк CSV из трёх чисел
TEST(CSVParserTest, BasicParsing) {
    std::istringstream ss("1,2,3\n4,5,6\n");
    CSVParser<int,int,int> parser(ss);

    auto it = parser.begin();
    auto end = parser.end();

    ASSERT_NE(it, end);
    EXPECT_EQ(*it, std::make_tuple(1,2,3));
    ++it;

    ASSERT_NE(it, end);
    EXPECT_EQ(*it, std::make_tuple(4,5,6));
    ++it;

    ASSERT_EQ(it, end);
}

// Проверяет, что пропускается указанное количество строк
TEST(CSVParserTest, SkipLines) {
    std::istringstream ss("skip\nskip2\n10,20\n");
    CSVParser<int,int> parser(ss, 2);

    auto it = parser.begin();
    EXPECT_EQ(*it, std::make_tuple(10,20));
}

// Проверяет корректный разбор значений с кавычками и запятой внутри
TEST(CSVParserTest, QuotedValues) {
    std::istringstream ss("\"10,11\",20\n");
    CSVParser<std::string,int> parser(ss);

    auto it = parser.begin();
    ASSERT_EQ(*it, std::make_tuple(std::string("10,11"), 20));
}

// Проверяет ошибку при неверном числе колонок в строке
TEST(CSVParserTest, WrongColumnCount) {
    std::istringstream ss("1,2\n1,2,3\n");
    CSVParser<int,int,int> parser(ss);

    EXPECT_THROW({
        parser.begin();
    }, CSVError);
}

// Проверяет ошибку конвертации текста в число
TEST(CSVParserTest, ConversionError) {
    std::istringstream ss("1,abc\n");
    CSVParser<int,int> parser(ss);

    EXPECT_THROW({
        parser.begin();
    }, CSVError);
}

// Проверяет работу с пустым вводом (итератор сразу равен end)
TEST(CSVParserTest, EmptyInput) {
    std::istringstream ss("");
    CSVParser<int,int> parser(ss);

    auto it = parser.begin();
    auto end = parser.end();
    EXPECT_EQ(it, end);
}

// Проверяет парсинг с пользовательскими разделителями
TEST(CSVParserTest, CustomDelimiters) {
    CSVConfig cfg;
    cfg.col_delim = ';';
    cfg.row_delim = '\n';

    std::istringstream ss("1;2;3\n4;5;6\n");
    CSVParser<int,int,int> parser(ss, 0, cfg);

    auto it = parser.begin();
    EXPECT_EQ(*it, std::make_tuple(1,2,3));
    ++it;
    EXPECT_EQ(*it, std::make_tuple(4,5,6));
}





// Проверяет разбор значений с пробелами вокруг
TEST(CSVParserTest, TrimSpaces) {
    std::istringstream ss("  1 , 2 ,  3 \n");
    CSVParser<int,int,int> parser(ss);

    auto it = parser.begin();
    EXPECT_EQ(*it, std::make_tuple(1,2,3));
}


// Проверяет большие числа для переполнения
TEST(CSVParserTest, IntegerOverflow) {
    std::istringstream ss("99999999999999999999,2\n");
    CSVParser<long long,int> parser(ss);

    EXPECT_THROW({
        parser.begin();
    }, CSVError);
}


// Проверяет строку с лишними разделителями
TEST(CSVParserTest, TrailingDelimiter) {
    std::istringstream ss("1,2,3,\n");
    CSVParser<int,int,int> parser(ss);

    EXPECT_THROW({ parser.begin(); }, CSVError);
}


// Очень длинная строка (например 10000 символов)
TEST(CSVParserTest, VeryLongLine) {
    std::string big(10000, 'x');
    std::istringstream ss(big + ",1\n");

    CSVParser<std::string,int> parser(ss);
    auto it = parser.begin();

    EXPECT_EQ(std::get<0>(*it), big);
    EXPECT_EQ(std::get<1>(*it), 1);
}


// Строка, заканчивающаяся без разделителя строки
TEST(CSVParserTest, LastLineWithoutNewline) {
    std::istringstream ss("1,2,3");
    CSVParser<int,int,int> parser(ss);

    auto it = parser.begin();
    EXPECT_EQ(*it, std::make_tuple(1,2,3));
    ++it;

    EXPECT_EQ(it, parser.end());
}
