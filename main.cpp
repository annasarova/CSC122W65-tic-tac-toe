#include <iostream>
#include <limits>
#include "src/tictactoe.hpp"
#include "src/humanplayer.hpp"
#include "src/computerplayer.hpp"

int main() {
  // Your driver program goes here
  bool exit_game = false;

  std::cout << "Welcome to Tic-Tac-Toe!\n\n";

  while (!exit_game) {
    short mode;

    std::cout << "What kind of game would you like to play?\n";
    std::cout << "1. Human vs. Human\n";
    std::cout << "2. Human vs. Computer\n";
    std::cout << "3. Computer vs. Human\n";
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
    else {
      Player* p1;
      Player* p2;
      if (mode == 1) {
        std::cout << "\nGreat! You will play against Human.\n";
        p1 = new HumanPlayer('X');
        p2 = new HumanPlayer('O');
      }
      else if (mode == 2) {
        std::cout << "\nGreat! You will play against computer.\n";
        p1 = new HumanPlayer('X');
        p2 = new ComputerPlayer('O');
      }
      else if (mode == 3) {
        std::cout << "\nGreat! The computer will go first.\n";
        p1 = new ComputerPlayer('X');
        p2 = new HumanPlayer('O');
      }

      bool play_again = true;

      while(play_again) {
        TicTacToe game(p1, p2);
        bool game_over = false;

        std::cout << "Board positions are numbered 1-9.\n";

        while(!game_over) {
          bool valid_move = game.play_turn();

          if (valid_move) {
            if (game.check_win()) {
              game.display_board();
              std::cout << "Player "
                        << game.get_last_player()->get_symbol()
                        << " wins!\n";
              game_over = true;
            }
            else if (game.check_draw()) {
              game.display_board();
              std::cout << "It's a draw!\n";
              game_over = true;
            }
            else {
              game.switch_player();
            }
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
          std::cout << "Thanks for playing!\n ";
        }
      }
      delete p1;
      delete p2;
    }
  }

  std::cout << "Goodbye!\n";

  return 0;
}
