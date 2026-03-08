#include <vector>

class Board {
private:
    std::vector<char> cells;

public:
    Board();

    void display() const;

    bool is_valid_move(short position) const;

    void place_mark(short position, char player);

    bool is_full() const;

    char get_cell(short index) const;
};
