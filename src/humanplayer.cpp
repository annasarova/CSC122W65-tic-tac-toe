#include "humanplayer.hpp"
#include <iostream>

#include <string>

//helper function to trim string
static std::string trim(const std::string& str) {
    size_t start = 0, end = str.length();

    while (start < end && isspace(str[start])) {
        start++;
    }
    while (end > start && isspace(str[end - 1])) {
        end--;
    }
    return str.substr(start, end - start);
}

HumanPlayer::HumanPlayer(char symbol) : Player(symbol) {}

short HumanPlayer::get_move(const Board &board) {
    std::string input;
    short move = -1;
    bool valid = false;

    while(!valid) {
        std::getline(std::cin, input);

        input = trim(input);

        valid = true;

        if(input.empty()) {
            valid = false;
        }
        else {
            try {
                size_t pos;
                short temp = static_cast<short>(std::stoi(input, &pos));

                // ensure no extra characters (e.g. "5 6")
                if(pos != input.length()) {
                    valid = false;
                }
                else {
                    move = temp;
                }
            }
            catch (...) {
                valid = false;
            }
        }

        if (!valid) {
            std::cout<<"Invalid input. Please enter a number from 1-9:";
            move =  -1;
        }
    }
    return move;
}

