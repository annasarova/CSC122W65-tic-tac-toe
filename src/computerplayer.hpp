#include "player.hpp"

class ComputerPlayer : public Player {
public:
    ComputerPlayer(char symbol);
    short get_move(const Board &board) override;

};