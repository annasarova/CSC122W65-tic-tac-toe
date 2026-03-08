#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"

TEST_CASE("Initial player is X") {
    TicTacToe game;
    REQUIRE(game.get_current_player() == 'X');
}

TEST_CASE("Valid moves are accepted") {
    TicTacToe game;
    REQUIRE(game.make_move(1) == true);
    REQUIRE(game.make_move(5) == true);
}

TEST_CASE("Invalid moves are rejected") {
    TicTacToe game;
    game.make_move(1); // X takes position 1
    REQUIRE(game.make_move(1) == false); // Cannot overwrite
    REQUIRE(game.make_move(0) == false); // Invalid position
    REQUIRE(game.make_move(10) == false); // Invalid position
}

TEST_CASE("Player switching works correctly") {
    TicTacToe game;
    REQUIRE(game.get_current_player() == 'X');
    game.switch_player();
    REQUIRE(game.get_current_player() == 'O');
    game.switch_player();
    REQUIRE(game.get_current_player() == 'X');
}

TEST_CASE("Horizontal win is detected") {
    TicTacToe game;
    // X takes top row
    game.make_move(1);
    game.make_move(4); // O
    game.make_move(2);
    game.make_move(5); // O
    game.make_move(3); // X wins
    REQUIRE(game.check_win() == true);
}

TEST_CASE("Vertical win is detected") {
    TicTacToe game;
    // X takes left column
    game.make_move(1);
    game.make_move(2); // O
    game.make_move(4);
    game.make_move(5); // O
    game.make_move(7); // X wins
    REQUIRE(game.check_win() == true);
}

TEST_CASE("Diagonal win is detected") {
    TicTacToe game;
    game.make_move(1); // X
    game.make_move(2); // O
    game.make_move(5); // X
    game.make_move(3); // O
    game.make_move(9); // X wins diagonally
    REQUIRE(game.check_win() == true);
}

TEST_CASE("Draw game is detected") {
    TicTacToe game;

    // Fill board with no winner
    game.make_move(1); // X
    game.switch_player();
    game.make_move(2); // O
    game.switch_player();
    game.make_move(3); // X
    game.switch_player();
    game.make_move(5); // O
    game.switch_player();
    game.make_move(4); // X
    game.switch_player();
    game.make_move(6); // O
    game.switch_player();
    game.make_move(8); // X
    game.switch_player();
    game.make_move(7); // O
    game.switch_player();
    game.make_move(9); // X

    REQUIRE(game.check_draw() == true);
}
