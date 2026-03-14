#include <string>
#include "tictactoe.hpp"
#include <limits>
#include <iostream>

// Your code goes here
TicTacToe::TicTacToe() {
    current_player = 'X';
}

char TicTacToe::get_current_player() const {
    return current_player;
}

short TicTacToe::get_valid_move() const {
    short move;

    while(!(std::cin >> move)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number from 1-9:";
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