#include <iostream>

#include "src/tictactoe.hpp"

int main() {
  // Your driver program goes here
  std::cout << "Welcome to Tic-Tac-Toe!\n";
  std::cout << "Board positions are numbered 1-9.\n";

  TicTacToe game;

  bool game_over = false;

  while(!game_over) {
    game.display_board();

    short move;

    std::cout << "Player "
              << game.get_current_player()
              << ", enter your move: ";

    std::cin >> move;

    if(!game.make_move(move)) {
      std::cout << "Invalid move. Try again.\n";
      continue;
    }

    if(game.check_win()) {
      game.display_board();
      std::cout << "Player "
                << game.get_current_player()
                << " wins!\n";
      game_over = true;
    }
    else if(game.check_draw()) {
      game.display_board();
      std::cout << "It's a draw!\n";
      game_over = true;
    }
    else {
      game.switch_player();
    }
  }

  return 0;
}
