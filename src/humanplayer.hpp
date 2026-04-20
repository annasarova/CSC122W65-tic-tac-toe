#include "player.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer(char symbol);
    short get_move(const Board &board) override;
};