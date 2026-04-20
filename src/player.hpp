#pragma once
#include "board.hpp"

class Player {
protected:
    char symbol;

public:
    Player(char symbol);
    virtual ~Player() = default;

    char get_symbol() const;

    virtual short get_move(const Board &board) = 0;
};