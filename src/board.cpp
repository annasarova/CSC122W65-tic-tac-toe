#include "board.hpp"
#include <iostream>

Board::Board() {
    cells = {'1','2','3','4','5','6','7','8','9'};
}

void Board::display() const {
    std::cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n";
}

bool Board::is_valid_move(short position) const {
    bool valid = true;

    if(position < 1 || position > 9) {
        valid = false;
    }
    else {
        if(cells[position-1] == 'X' || cells[position-1] == 'O') {
            valid = false;
        }
    }

    return valid;
}

void Board::place_mark(short position, char player) {
    cells[position-1] = player;
}

bool Board::is_full() const {
    bool full = true;

    for(size_t i = 0; i < cells.size(); i++) {
        if(cells[i] != 'X' && cells[i] != 'O') {
            full = false;
        }
    }

    return full;
}

char Board::get_cell(short index) const {
    return cells[index];
}
