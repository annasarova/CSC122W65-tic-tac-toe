#include <string>
#include "board.hpp"
#include "player.hpp"

// Your functions go here
class TicTacToe {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* current_player;
    Player* last_player;

public:
    TicTacToe(Player* p1, Player* p2);

    Player* get_last_player() const;

    void display_board() const;

    bool make_move(short position);

    void switch_player();

    bool check_win() const;

    bool check_draw() const;

    bool play_turn();
};