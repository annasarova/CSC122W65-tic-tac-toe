#include "computerplayer.hpp"

ComputerPlayer::ComputerPlayer(char symbol) : Player(symbol) {}

short ComputerPlayer::get_move(const Board &board) {
    short move = -1;

    for(short i = 1; i <= 9; i++) {
        if(board.is_valid_move(i)) {
            move = i;
            break;
        }
    }
    return move;
}
