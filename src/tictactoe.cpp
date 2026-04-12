#include <string>
#include "tictactoe.hpp"
#include <iostream>
#include <cctype>

//helper function to trim string
static std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    while(start < end && std::isspace(str[start])) {
        start++;
    }

    while(end > start && std::isspace(str[end - 1])) {
        end--;
    }

    return str.substr(start, end - start);
}

// Your code goes here
TicTacToe::TicTacToe() {
    current_player = 'X';
}

char TicTacToe::get_current_player() const {
    return current_player;
}

short TicTacToe::get_valid_move() const {
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

bool TicTacToe::make_move(short position) {
    bool success = false;
    if(board.is_valid_move(position)) {
        board.place_mark(position, current_player);
        success = true;
    }

    return success;
}

void TicTacToe::switch_player() {
    if(current_player == 'X') {
        current_player = 'O';
    }
    else {
        current_player = 'X';
    }
}

void TicTacToe::display_board() const {
    board.display();
}

bool TicTacToe::check_draw() const {
    return board.is_full();
}

bool TicTacToe::check_win() const {
    bool win = false;

    int wins[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
    };

    for(short i = 0; i < 8; i++) {
        char a = board.get_cell(wins[i][0]);
        char b = board.get_cell(wins[i][1]);
        char c = board.get_cell(wins[i][2]);

        if(a == b && b == c)
            win = true;
    }

    return win;
}

void TicTacToe::computer_move() {
    for(short i = 0; i <= 9; i++) {
        if(board.is_valid_move(i)) {
            board.place_mark(i, current_player);
            return;
        }
    }
}
