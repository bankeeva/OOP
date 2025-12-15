#include "gtest/gtest.h"
#include "Obeder.h"
#include "ObederReceipt.h"
#include <sstream>
#include <vector>
#include <algorithm>

// Тестирование класса Obeder
TEST(ObederTest, SetAndGet) {
    Obeder person;
    std::time_t ts = 1700000000;
    std::string user = "superIgor2000";
    long long sum = 12345;

    person.setTime(ts);
    person.setUser(user);
    person.setSum(sum);

    EXPECT_EQ(person.getTime(), ts);
    EXPECT_EQ(person.getUser(), user);
    EXPECT_EQ(person.getSum(), sum);
}

// Тестирование класса ObederReceipt: добавление записей
TEST(ObederReceiptTest, AddPerson) {
    ObederReceipt receipt;
    Obeder p1;
    p1.setUser("user1");
    p1.setSum(500);

    receipt.setPerson(p1);
    std::vector<Obeder> people = receipt.getPerson();

    ASSERT_EQ(people.size(), 1);
    EXPECT_EQ(people[0].getUser(), "user1");
    EXPECT_EQ(people[0].getSum(), 500);
}

// Тестирование подсчета долгов
TEST(ObederReceiptTest, CalcDebt) {
    ObederReceipt receipt;

    Obeder p1;
    p1.setUser("user1");
    p1.setSum(-500);  // должен вернуть 500
    receipt.setPerson(p1);

    Obeder p2;
    p2.setUser("user2");
    p2.setSum(500);  // должен получить 500
    receipt.setPerson(p2);

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    receipt.calcDebt();

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();

    EXPECT_NE(output.find("user1 -> user2 - 5 р 0 коп"), std::string::npos);
}

// Тест с несколькими участниками
TEST(ObederReceiptTest, CalcDebt_NewExample) {
    ObederReceipt receipt;

    Obeder bob;   bob.setUser("bob");   bob.setSum(21234);   receipt.setPerson(bob);
    Obeder alice; alice.setUser("alice"); alice.setSum(-21000); receipt.setPerson(alice);
    Obeder mark;  mark.setUser("mark");  mark.setSum(-234);    receipt.setPerson(mark);

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    receipt.calcDebt();

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();

    EXPECT_NE(output.find("alice -> bob - 210 р 0 коп"), std::string::npos);
    EXPECT_NE(output.find("mark -> bob - 2 р 34 коп"), std::string::npos);
}
