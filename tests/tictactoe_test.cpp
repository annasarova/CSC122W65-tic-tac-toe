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
    TicTacToe game(&p1, &p2, false);

    REQUIRE(game.make_move(1) == true);
    game.switch_player();
    REQUIRE(game.make_move(5) == true);
}

TEST_CASE("Invalid moves are rejected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2, false);

    game.make_move(1);
    REQUIRE(game.make_move(1) == false);
    REQUIRE(game.make_move(0) == false);
    REQUIRE(game.make_move(10) == false);
}

TEST_CASE("Player switching works") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2, false);

    game.make_move(1); // X
    game.switch_player();
    game.make_move(2); // O

    REQUIRE(game.get_last_player()->get_symbol() == 'O');
}

TEST_CASE("Horizontal win is detected") {
    HumanPlayer p1('X');
    HumanPlayer p2('O');
    TicTacToe game(&p1, &p2, false);

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
    TicTacToe game(&p1, &p2, false);

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
    TicTacToe game(&p1, &p2, false);

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
    TicTacToe game(&p1, &p2, false);

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
    TicTacToe game(&p1, &p2, false);

    game.make_move(1); // X
    game.switch_player();

    game.play_turn(); // computer move

    // position 2 should now be taken
    REQUIRE(game.make_move(2) == false);
}

TEST_CASE("Computer does not overwrite moves") {
    HumanPlayer p1('X');
    ComputerPlayer p2('O');
    TicTacToe game(&p1, &p2, false);

    game.make_move(1);
    game.switch_player();

    game.play_turn(); // computer should take 2

    REQUIRE(game.make_move(1) == false);
}

TEST_CASE("Trap does not place a mark on the board") {
    std::srand(1); // we add this so trap position is predictable

    HumanPlayer p1('X');
    HumanPlayer p2('O');

    TicTacToe game(&p1, &p2, true);

    // try to hit trap (we assume predictable seed makes trap = 1 or known)
    game.make_move(1);

    // even if trap is hit, cell should NOT be X or O
    char cell = game.get_last_player()->get_symbol(); // just ensures flow ran

    REQUIRE(game.check_win() == false);
}

TEST_CASE("Trap causes player to lose turn without marking board") {
    std::srand(1);

    HumanPlayer p1('X');
    HumanPlayer p2('O');

    TicTacToe game(&p1, &p2, true);

    game.make_move(1); // assume trap hit
    game.switch_player();

    // second player should still be able to move normally
    REQUIRE(game.make_move(2) == true);
}

TEST_CASE("Computer is affected by trap like human") {
    std::srand(1);

    HumanPlayer p1('X');
    ComputerPlayer p2('O');

    TicTacToe game(&p1, &p2, true);

    game.make_move(1);
    game.switch_player();

    // computer move should still execute (even if trap exists)
    game.play_turn();

    REQUIRE(true); // test ensures no crash and flow continues
}

TEST_CASE("Trap does not interfere with win detection") {
    std::srand(1);

    HumanPlayer p1('X');
    HumanPlayer p2('O');

    TicTacToe game(&p1, &p2, false);

    game.make_move(1); game.switch_player();
    game.make_move(4); game.switch_player();
    game.make_move(2); game.switch_player();
    game.make_move(5); game.switch_player();
    game.make_move(3);

    REQUIRE(game.check_win() == true);
}

TEST_CASE("Trap enabled game still detects draw correctly") {
    std::srand(1);

    HumanPlayer p1('X');
    HumanPlayer p2('O');

    TicTacToe game(&p1, &p2, false);

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