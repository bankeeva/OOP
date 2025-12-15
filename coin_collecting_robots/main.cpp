#include <iostream>
#include <map>
#include <cmath>
#include "Field.h"
#include "Strategy.h"
#include "GreedyStrategy.h"
#include "LadderStrategy.h"
#include "RandomDStrategy.h"
#include "RandomVHStrategy.h"
#include "BounceStrategy.h"


std::vector<std::unique_ptr<Strategy>> strategies;


std::map<int, std::function<std::unique_ptr<Strategy>()>> factory = {
    {1, [](){ return std::make_unique<RandomVHStrategy>(); }},
    {2, [](){ return std::make_unique<RandomDStrategy>(); }},
    {3, [](){ return std::make_unique<GreedyStrategy>(); }},
    {4, [](){ return std::make_unique<BounceStrategy>(); }},
    {5, [](){ return std::make_unique<LadderStrategy>(); }}
};

unsigned long all_strat = factory.size();


std::vector<std::string> printResults(const std::vector<std::unique_ptr<Strategy>>& _strategies)
{
    std::cout << "\n----- Результаты -----\n";
    int max_points = 0, min_steps = 10000;
    double min_dist = 10000;
    for (const auto& st : _strategies)
    {
        const int dx = st->getCurX() - st->getStartX();
        const int dy = st->getCurY() - st->getStartY();

        const double dist = std::sqrt(dx * dx + dy * dy);

        std::cout << "* Стратегия: " << st->name() << std::endl
                  << "    - Монет собрано: " << st->getCount() << std::endl
                  << "    - Шагов сделано: " << st->getSteps() << std::endl
                  << "    - Расстояние от старта: " << dist << std::endl << std::endl;

        if (max_points < st->getCount()) max_points = st->getCount();
    }

    std::vector<std::string> ans;
    std::vector<Strategy*> winner;
    for (const auto& st : _strategies)
    {
        if (st->getCount() == max_points)
            winner.push_back(st.get());
    }

    if (winner.size() == 1)
    {
        ans.push_back(winner[0]->name());
        return ans;
        // std::cout << "ПОБЕДИТЕЛЬ: " << winner[0]->name() << std::endl;
    }
    else
    {
        std::vector<Strategy*> winner2;
        for (const auto& st : winner)
        {
            if (st->getSteps() < min_steps)
                min_steps = st->getSteps();
        }
        for (const auto& st : winner)
        {
            if (st->getSteps() == min_steps)
                winner2.push_back(st);
        }

        if (winner2.size() == 1)
        {
            ans.push_back(winner2[0]->name());
            return ans;
            // std::cout << "ПОБЕДИТЕЛЬ: " << winner2[0]->name() << std::endl;
        }
        else
        {
            std::vector<Strategy*> winner3;
            for (const auto& st : winner2)
            {
                const int dx = st->getCurX() - st->getStartX();
                const int dy = st->getCurY() - st->getStartY();

                if (std::abs(std::sqrt(dx*dx + dy*dy) - min_dist) > 1e-6)
                    min_dist = std::sqrt(dx*dx + dy*dy);
            }
            for (const auto& st : winner2)
            {
                const int dx = st->getCurX() - st->getStartX();
                const int dy = st->getCurY() - st->getStartY();

                if (std::abs(std::sqrt(dx*dx + dy*dy) - min_dist) < 1e-6)
                    winner3.push_back(st);
            }
            if (winner3.size() == 1)
            {
                ans.push_back(winner3[0]->name());
                return ans;
                // std::cout << "ПОБЕДИТЕЛЬ: " << winner3[0]->name() << std::endl;
            }
            else
            {
                // std::cout << "ПОБЕДИТЕЛИ: "<< std::endl;
                for (int i = 0; i < winner3.size(); i++)
                {
                    ans.push_back(winner3[i]->name());
                    // std::cout << "  " << winner3[i]->name()<< std::endl;
                }
                return ans;
            }
        }
    }
}

void detailed(Field field, const int W, const int H, const int P)
{
    field.initField(W, H, P);

    strategies.clear();
    int count_st;
    std::cout << "Введите количество стратегий (от 1 до " << all_strat << ")"  << std::endl;
    std::cin >> count_st;
    if (count_st > all_strat || count_st < 1)
    {
        std::cerr << "Число должно быть от 1 до " << all_strat << std::endl;
        exit(0);
    }

    std::cout << "Введите номера этих стратегий" << std::endl;
    strategies.reserve(count_st);

    for (int i = 0; i < count_st; i++)
    {
        int st;
        std::cin >> st;

        auto it = factory.find(st);
        if (it == factory.end())
        {
            std::cerr << "Такой стратегии нет\n";
            exit(0);
        }

        strategies.push_back(it->second());
    }

    for (auto& strat : strategies) {
        int x = rand() % field.getWidth();
        int y = rand() % field.getHeight();
        strat->setStart(x, y);
    }

    std::cout << "\nНачальное поле" << std::endl;
    field.print();
    int step = 0;
    do
    {
        for (auto& strat : strategies) {
            strat->nextMove(field);
        }
        std::cout << "\nШаг " << ++step << std::endl;
        field.print();
        std::cout << "Что бы выйти нажми q, иначе - любой символ" << std::endl;
        char c;
        std::cin >> c;
        if (c == 'q') break;
    } while (1);

    const std::vector<std::string> winners = printResults(strategies);
    std::cout << "ПОБЕДИТЕЛЬ!:" << std::endl;
    for (std::string w : winners)
    {
        std::cout << "  " << w << std::endl;
    }
}

void fast(Field field, const int W, const int H, const int P)
{
    strategies.clear();
    std::cout << "Введите 4 номера используемых стратегий" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        int st;
        std::cin >> st;
        if (st < 1 || st > all_strat)
        {
            std::cerr << "Такой стратегии нет" << std::endl;
            exit(0);
        }
        strategies.push_back(factory[st]());
    }

    int N, M, K;
    std::cout << "Введите N - количество ходов, M - сколько монет нужно собрать, K - количество игр" << std::endl;
    std::cin >> N >> M >> K;
    if (N <= 0 || M < 0 || K <= 0)
    {
        std::cerr << "количество ходов и игр больше нуля, а количество монет не отрицательным" << std::endl;
        exit(0);
    }

    for (int i = 0; i < K; i++)
    {
        field.initField(W, H, P);

        int collect_points = M;

        for (auto& strat : strategies) {
            int x = rand() % field.getWidth();
            int y = rand() % field.getHeight();
            strat->setStart(x, y);
        }

        for (int n = 0; n < N; n++)
        {
            for (auto& strat : strategies) {
                strat->nextMove(field);
                if (field.getCounterPoints() < collect_points) collect_points--;
                if (collect_points == 0) break;
            }
            if (collect_points == 0) break;
        }
        const std::vector<std::string> winners = printResults(strategies);
        std::cout << "ПОБЕДИТЕЛЬ!:" << std::endl;
        for (std::string w : winners)
        {
            std::cout << "  " << w << std::endl;
        }
    }
}

void tournament(Field field, const int W, const int H, const int P)
{
    strategies.clear();
    for (const auto& f : factory)
        strategies.push_back(f.second());

    std::cout << "Введите количество ходов для одной игры" << std::endl;
    int K;
    std::cin >> K;
    if (K < 0)
    {
        std::cerr << "Число должно быть больше 0" << std::endl;
        exit(0);
    }

    std::vector<std::string> abs_winners;
    for (int i = 0; i < all_strat - 1; i++)
    {
        for (int j = i + 1; j < all_strat; j++)
        {
            field.initField(W, H, P);
            for (auto& strat : strategies) {
                int x = rand() % field.getWidth();
                int y = rand() % field.getHeight();
                strat->setStart(x, y);
                strat->reset();
            }

            for (int k = 0; k < K; k++)
            {
                strategies[i]->nextMove(field);
                strategies[j]->nextMove(field);
            }
            std::cout << std::endl << "ТУРНИР МЕЖДУ: " << strategies[i]->name() << " и " << strategies[j]->name() << std::endl;
            const std::vector<std::string> winners = printResults(strategies);
            std::cout << "Победитель тура:" << std::endl;
            for (std::string w : winners)
            {
                std::cout << "  " << w << std::endl;
                abs_winners.push_back(w);
            }
        }
    }

    std::cout << std::endl << "------- ПОБЕДИТЕЛЬ ТУРНИРА -------" << std::endl;
    std::unordered_map<std::string, int> freq;
    for (const auto& s : abs_winners) freq[s]++;

    int maxCount = 0;
    for (auto& p : freq) {
        maxCount = std::max(maxCount, p.second);
    }

    for (auto& p : freq) {
        if (p.second == maxCount)
            std::cout << "  " << p.first << std::endl;
    }
}


int main()
{
    int game_mod = 0;
    std::cout << "Введите цифру - режим игры:\n"
                 "  1. Подробный режим\n"
                 "  2. Быстрый режим\n"
                 "  3. Турнирный режим" << std::endl;
    std::cin >> game_mod;
    if (game_mod < 1 || game_mod > 3)
    {
        std::cerr << "Такого режима нет" << std::endl;
        return 0;
    }

    int H, W, P;
    const Field field;
    std::cout << "Введите параметры поля Высота, Ширина, количество монет" << std::endl;
    std::cin >> H >> W >> P;

    switch (game_mod)
    {
        case 1: detailed(field, H, W, P); break;
        case 2: fast(field, H, W, P); break;
        case 3: tournament(field, H, W, P); break;
        default: break;
    }

    return 0;
}
