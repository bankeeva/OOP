#include "Obeder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ObederReceipt.h"


int main()
{
    std::string inputFileName, line;
    std::cin >> inputFileName;
    std::ifstream file(inputFileName);

    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << inputFileName << std::endl;
        return 0;
    }

    Obeder person;
    ObederReceipt company;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream val(line);
        std::time_t ts;
        std::string user_id;
        long long sum;
        try
        {
            val >> ts;
            val >> user_id;
            val >> sum;
        } catch (const std::ios_base::failure& e)
        {
            std::cout << "Ошибка чтения файла: " << e.what() << std::endl;
            return 0;
        }
        person.setTime(ts);
        person.setUser(user_id);
        person.setSum(sum);

        company.setPerson(person);
    }
    file.close();

    company.calcDebt();

    return 0;
}
