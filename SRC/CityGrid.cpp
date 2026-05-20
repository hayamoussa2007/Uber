#include "CityGrid.h"
#include <iostream>

using namespace std;

CityGrid::CityGrid() {
    rows = 10;
    cols = 10;
    cells = vector<vector<char>>(rows, vector<char>(cols, '.'));
}

CityGrid::CityGrid(int rowCount, int colCount) {
    rows = rowCount;
    cols = colCount;
    cells = vector<vector<char>>(rows, vector<char>(cols, '.'));
}

int CityGrid::getRows() const {
    return rows;
}

int CityGrid::getCols() const {
    return cols;
}

bool CityGrid::isValidPosition(Position p) const {
    return p.row >= 0 && p.row < rows && p.col >= 0 && p.col < cols;
}

bool CityGrid::isBlocked(Position p) const {
    return isValidPosition(p) && cells[p.row][p.col] == 'X';
}

bool CityGrid::isEmpty(Position p) const {
    return isValidPosition(p) && cells[p.row][p.col] == '.';
}

char CityGrid::getCell(Position p) const {
    if (isValidPosition(p)) {
        return cells[p.row][p.col];
    }

    return '?';
}

void CityGrid::setCell(Position p, char value) {
    if (isValidPosition(p)) {
        cells[p.row][p.col] = value;
    }
}

void CityGrid::addBlockedCell(Position p) {
    if (isEmpty(p)) {
        cells[p.row][p.col] = 'X';
    }
}

void CityGrid::addDriver(Position p) {
    if (isEmpty(p)) {
        cells[p.row][p.col] = 'D';
    }
}

void CityGrid::setPickup(Position p) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (cells[r][c] == 'P') {
                cells[r][c] = '.';
            }
        }
    }

    if (isEmpty(p)) {
        cells[p.row][p.col] = 'P';
    }
}

void CityGrid::setDestination(Position p) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (cells[r][c] == 'R') {
                cells[r][c] = '.';
            }
        }
    }

    if (isEmpty(p)) {
        cells[p.row][p.col] = 'R';
    }
}

void CityGrid::clearPath() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (cells[r][c] == '*') {
                cells[r][c] = '.';
            }
        }
    }
}

void CityGrid::markPath(const vector<Position>& path) {
    for (const Position& p : path) {
        if (isValidPosition(p) && cells[p.row][p.col] == '.') {
            cells[p.row][p.col] = '*';
        }
    }
}

void CityGrid::display() const {
    cout << "\nCity Grid:\n\n";

    cout << "   ";
    for (int c = 0; c < cols; c++) {
        cout << c << ' ';
    }
    cout << '\n';

    for (int r = 0; r < rows; r++) {
        cout << r << "  ";
        for (int c = 0; c < cols; c++) {
            cout << cells[r][c] << ' ';
        }
        cout << '\n';
    }
}

vector<vector<char>> CityGrid::getCells() const {
    return cells;
}