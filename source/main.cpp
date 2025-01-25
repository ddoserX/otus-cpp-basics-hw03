#include "mechanics/rand.hpp"
#include "mechanics/score_table.hpp"
#include <iostream>

bool get_guess(int &);
bool confirm_restart_game();
void reset_game_data(int &, int &, bool &);
void args_handler(int, char **);

int main(int argc, char **args)
{
    const int MAX_ATTEMPTS = 10;

    args_handler(argc, args);

    hw03::init_seed();
    hw03::init_player();
    hw03::load_score_table();

    bool is_game_finished = false;

    int attempts = 0;
    int wish_number = hw03::get_wish_number();

    int guess = -1;

    do
    {
        if (get_guess(guess) == false)
        {
            continue;
        }
        ++attempts;

        if (guess > wish_number)
        {
            std::cout << "less than: " << guess << std::endl;
        }
        else if (guess < wish_number)
        {
            std::cout << "greater than: " << guess << std::endl;
        }
        else
        {
            std::cout << "You win! Attempts: " << attempts << std::endl;
            hw03::increase_player_score();
            is_game_finished = true;
        }

        if (attempts > MAX_ATTEMPTS)
        {
            std::cout << "You lose! Attempts: " << attempts << std::endl;
            is_game_finished = true;
        }

        if (is_game_finished)
        {
            hw03::check_and_record_score();
            hw03::print_score_table();
            hw03::save_score_table();

            if (confirm_restart_game() == false)
            {
                break;
            }

            reset_game_data(wish_number, attempts, is_game_finished);
        }

    } while (true);
}

bool get_guess(int &guess)
{
    std::cout << "Enter your guess: ";
    std::cin >> guess;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }

    return true;
}

bool confirm_restart_game()
{
    std::cout << "Restart game? (Enter: {yes} to positive choice): ";

    std::string choice{};
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }

    if (choice == "yes")
    {
        return true;
    }

    return false;
}

void reset_game_data(int &wish, int &attemps, bool &is_game_finished)
{
    wish = hw03::get_wish_number();
    attemps = 0;
    is_game_finished = false;
}

void args_handler(int count, char **args)
{
    if (count < 2)
    {
        return;
    }

    if (count == 2)
    {
        std::string arg = args[1];

        if (arg == "-table")
        {
            hw03::load_score_table();
            hw03::print_score_table();
            exit(0);
        }
    }

    if (count == 3)
    {
        std::string arg = args[1];

        if (arg == "-max")
        {
            int value = std::atoi(args[2]);
            hw03::set_random_max(value);
        }
        else if (arg == "-level")
        {
            int value = std::atoi(args[2]);
            hw03::set_random_level(value);
        }
    }
}
