#include "score_table.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace hw03
{
const std::string SAVE_FILE = "./save.dat";

struct score_data
{
    std::string name;
    int score;
} player_data;

std::vector<score_data> score_table;

bool init_player()
{
    std::cout << "Hi! Enter your name, please: ";
    std::cin >> player_data.name;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }

    player_data.score = 0;

    return true;
}

void increase_player_score()
{
    player_data.score += 1;
}

void check_and_record_score(const score_data &data)
{
    if (score_table.size() == 0)
    {
        score_table.push_back(data);
        return;
    }

    auto comp = [](const score_data &pd1, const score_data &pd2) -> bool { return pd1.score > pd2.score; };
    bool is_find = false;

    for (size_t i = 0; i < score_table.size(); i++)
    {
        if (score_table[i].name == data.name)
        {
            if (score_table[i].score < data.score)
            {
                score_table[i].score = data.score;
                std::sort(score_table.begin(), score_table.end(), comp);
            }

            is_find = true;
            break;
        }
    }

    if (is_find == false)
    {
        score_table.push_back(data);
        std::sort(score_table.begin(), score_table.end(), comp);
    }
}

void check_and_record_score()
{
    check_and_record_score(player_data);
}

void print_score_table()
{
    std::cout << "High scores table:" << std::endl;

    for (size_t i = 0; i < score_table.size(); i++)
    {
        std::cout << score_table[i].name << '\t' << score_table[i].score << std::endl;
    }
}

bool check_save_file_exists()
{
    std::ifstream fs_in{SAVE_FILE};
    if (!fs_in.is_open())
    {
        return false;
    }

    fs_in.close();
    return true;
}

bool save_score_table()
{
    std::ofstream fs_out{SAVE_FILE, std::ios::out | std::ios::binary};
    if (!fs_out.is_open())
    {
        return false;
    }

    for (size_t i = 0; i < score_table.size(); i++)
    {
        size_t name_size = score_table[i].name.size();

        fs_out.write((char *)&name_size, sizeof(name_size));
        fs_out.write(score_table[i].name.c_str(), sizeof(name_size));
        fs_out.write((char *)&score_table[i].score, sizeof(score_table[i].score));
    }

    fs_out.close();
    return true;
}

bool load_score_table()
{
    std::ifstream fs_in{SAVE_FILE, std::ios::in | std::ios::binary};
    if (!fs_in.is_open())
    {
        return false;
    }

    while (true)
    {
        size_t name_size = 0;
        std::string name{};
        int score = 0;

        fs_in.read((char *)&name_size, sizeof(name_size));
        name.resize(name_size);

        fs_in.read(name.data(), sizeof(name_size));
        fs_in.read((char *)&score, sizeof(score));

        if (fs_in.fail())
        {
            break;
        }

        check_and_record_score({name, score});
    }

    fs_in.close();
    return true;
}

} // namespace hw03
