#include "player.hpp"

Player::Player(char symbol) {
    this->symbol = symbol;
}

char Player::get_symbol() const {
    return symbol;
}
