#ifndef CITYGRID_H
#define CITYGRID_H

#include <vector>
#include "Position.h"

using namespace std;

class CityGrid {
private:
    int rows;
    int cols;
    vector<vector<char>> cells;

public:
    CityGrid();
    CityGrid(int rowCount, int colCount);

    int getRows() const;
    int getCols() const;

    bool isValidPosition(Position p) const;
    bool isBlocked(Position p) const;
    bool isEmpty(Position p) const;

    char getCell(Position p) const;
    void setCell(Position p, char value);

    void addBlockedCell(Position p);
    void addDriver(Position p);
    void setPickup(Position p);
    void setDestination(Position p);

    void clearPath();
    void markPath(const vector<Position>& path);

    void display() const;

    vector<vector<char>> getCells() const;
};

#endif