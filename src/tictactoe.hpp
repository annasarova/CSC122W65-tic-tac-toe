#include <string>
#include "board.hpp"

// Your functions go here
class TicTacToe {
private:
    Board board;
    char current_player;

public:
    TicTacToe();

    char get_current_player() const;

    short get_valid_move() const;

    bool make_move(short position);

    void switch_player();

    bool check_win() const;

    bool check_draw() const;

    void display_board() const;

    void computer_move();
};