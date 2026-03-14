#include <iostream>

#include "src/tictactoe.hpp"

int main() {
  // Your driver program goes here
  std::cout << "Welcome to Tic-Tac-Toe!\n";
  std::cout << "Board positions are numbered 1-9.\n";

  bool play_again = true;

  while(play_again) {
    TicTacToe game;
    bool game_over = false;

    while(!game_over) {
      game.display_board();

      std::cout << "Player "
                << game.get_current_player()
                << ", enter your move: ";

      short move = game.get_valid_move();

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

    char response;
    std::cout << "\nWould you like to play again? (y/n): ";
    std::cin >> response;

    while(response != 'y' && response != 'Y' && response != 'n' && response != 'N') {
      std::cout << "Invalid input. Please enter y or n: ";
      std::cin >> response;
    }
    if(response == 'n' || response == 'N') {
      play_again = false;
    }
  }

  std::cout << "Thanks for playing!\n ";
  return 0;
}
