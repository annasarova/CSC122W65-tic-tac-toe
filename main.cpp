#include <iostream>
#include <limits>
#include "src/tictactoe.hpp"

int main() {
  // Your driver program goes here
  short mode;
  bool exit_game = false;

  std::cout << "Welcome to Tic-Tac-Toe!\n";

  std::cout << "What kind of game would you like to play?\n";
  std::cout << "1. Human vs. Human\n";
  std::cout << "2. Human vs. Computer\n";
  std::cout << "3. Computer vs. Humanr\n";
  std::cout << "4. Exit\n\n";

  std::cout << "What is your selection? ";
  std::cin >> mode;

  while(mode < 1 || mode > 4 || std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid selection. Try again: ";
    std::cin >> mode;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if(mode == 4) {
    exit_game = true;
  }

  if (!exit_game) {
    if (mode == 2) {
      std::cout << "\nGreat! You will play against computer.\n";
    }
    else if (mode == 3) {
      std::cout << "\nGreat! The computer will go first.\n";
    }
  }

  bool play_again = true;

  while(play_again && !exit_game) {
    TicTacToe game;
    bool game_over = false;
    bool vs_computer = (mode == 2 || mode == 3);
    bool computer_first = (mode == 3);

    std::cout << "Board positions are numbered 1-9.\n";

    while(!game_over) {
      game.display_board();

      // COMPUTER TURN
      if(vs_computer &&
        ((computer_first && game.get_current_player() == 'X') ||
        (!computer_first && game.get_current_player() == 'O'))) {

        game.computer_move();
        std::cout << "Computer made a move!\n";
      }
      else {
        std::cout << "Player "
                  << game.get_current_player()
                  << ", enter your move: ";

        short move = game.get_valid_move();

        if(move == -1 || !game.make_move(move)) {
          std::cout << "Invalid move. Try again.\n";
          continue;
        }
      }

      // WIN CHECK
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
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(response == 'n' || response == 'N') {
      play_again = false;
    }
  }

  if (exit_game) {
    std::cout << "Goodbye!\n";
  }
  else {
    std::cout << "Thanks for playing!\n ";
  }

  return 0;
}
