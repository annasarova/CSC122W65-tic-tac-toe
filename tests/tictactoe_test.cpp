#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"
#include "../src/humanplayer.hpp"
#include "../src/computerplayer.hpp"

TEST_CASE("Valid moves are accepted") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    REQUIRE(game.make_move(1) == true);
    game.switch_player();
    REQUIRE(game.make_move(5) == true);
}

TEST_CASE("Invalid moves are rejected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1);
    REQUIRE(game.make_move(1) == false);
    REQUIRE(game.make_move(0) == false);
    REQUIRE(game.make_move(10) == false);
}

TEST_CASE("Player switching works") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); // X
    game.switch_player();
    game.make_move(2); // O

    REQUIRE(game.get_last_player()->get_symbol() == 'O');
}

TEST_CASE("Horizontal win is detected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); game.switch_player();
    game.make_move(4); game.switch_player();
    game.make_move(2); game.switch_player();
    game.make_move(5); game.switch_player();
    game.make_move(3);

    REQUIRE(game.check_win() == true);
}

TEST_CASE("Vertical win is detected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); game.switch_player();
    game.make_move(2); game.switch_player();
    game.make_move(4); game.switch_player();
    game.make_move(5); game.switch_player();
    game.make_move(7);

    REQUIRE(game.check_win() == true);
}

TEST_CASE("Diagonal win is detected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); game.switch_player();
    game.make_move(2); game.switch_player();
    game.make_move(5); game.switch_player();
    game.make_move(3); game.switch_player();
    game.make_move(9);

    REQUIRE(game.check_win() == true);
}

TEST_CASE("Draw is detected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); game.switch_player();
    game.make_move(2); game.switch_player();
    game.make_move(3); game.switch_player();
    game.make_move(5); game.switch_player();
    game.make_move(4); game.switch_player();
    game.make_move(6); game.switch_player();
    game.make_move(8); game.switch_player();
    game.make_move(7); game.switch_player();
    game.make_move(9);

    REQUIRE(game.check_draw() == true);
}

TEST_CASE("Computer picks first available move") {
    HumanPlayer p1('X');
    ComputerPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1); // X
    game.switch_player();

    game.play_turn(); // computer move

    // position 2 should now be taken
    REQUIRE(game.make_move(2) == false);
}

TEST_CASE("Computer does not overwrite moves") {
    HumanPlayer p1('X');
    ComputerPlayer p2('O');
    TicTacToe game(&p1, &p2);

    game.make_move(1);
    game.switch_player();

    game.play_turn(); // computer should take 2

    REQUIRE(game.make_move(1) == false);
}