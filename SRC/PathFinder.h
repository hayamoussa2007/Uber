#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include "Position.h"

using namespace std;

class PathFinder {
public:
    static bool isInsideGrid(int row, int col, int rows, int cols);

    static bool isWalkable(char cell);

    static vector<Position> findShortestPath(
        vector<vector<char>> grid,
        Position start,
        Position target
    );

    static int findShortestDistance(
        vector<vector<char>> grid,
        Position start,
        Position target
    );
};

#endif
