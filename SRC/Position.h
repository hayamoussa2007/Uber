#ifndef POSITION_H
#define POSITION_H

struct Position {
    int row;
    int col;

    Position() {
        row = 0;
        col = 0;
    }

    Position(int r, int c) {
        row = r;
        col = c;
    }

    bool operator==(Position other) {
        return row == other.row && col == other.col;
    }
};

#endif
