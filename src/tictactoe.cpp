#include <string>
#include "tictactoe.hpp"
#include <iostream>
#include <cctype>

#include "computerplayer.hpp"

// Your code goes here
TicTacToe::TicTacToe(Player* p1, Player* p2) {
    player1 = p1;
    player2 = p2;
    current_player = player1;
    last_player = nullptr;
}

Player* TicTacToe::get_last_player() const {
    return last_player;
}

void TicTacToe::display_board() const {
    board.display();
}

bool TicTacToe::make_move(short position) {
    bool success = false;
    if(board.is_valid_move(position)) {
        board.place_mark(position, current_player->get_symbol());
        success = true;

        last_player = current_player;
    }
    return success;
}

void TicTacToe::switch_player() {
    last_player = current_player;

    if(current_player == player1) {
        current_player = player2;
    }
    else {
        current_player = player1;
    }
}

bool TicTacToe::check_draw() const {
    return board.is_full();
}

bool TicTacToe::check_win() const {
    bool win = false;

    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
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

bool TicTacToe::play_turn() {
    bool success = true;
    display_board();

    if (dynamic_cast<ComputerPlayer*>(current_player)) {
        std::cout << "Computer is making a move...\n";
    }
    else {
        std::cout << "Player "
              << current_player->get_symbol()
              << ", enter your move: ";
    }

    short move = current_player->get_move(board);

    if (!make_move(move)) {
        std::cout << "Invalid move. Try again. " << std::endl;
        success = false;
    }

    return success;
}
