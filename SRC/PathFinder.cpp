#include "PathFinder.h"
#include <queue>

using namespace std;

bool PathFinder::isInsideGrid(int row, int col, int rows, int cols) {
    if (row < 0) {
        return false;
    }

    if (row >= rows) {
        return false;
    }

    if (col < 0) {
        return false;
    }

    if (col >= cols) {
        return false;
    }

    return true;
}

bool PathFinder::isWalkable(char cell) {
    if (cell == 'X') {
        return false;
    }

    return true;
}

void swapPositions(Position& a, Position& b) {
    Position temp = a;
    a = b;
    b = temp;
}

void reversePath(vector<Position>& path) {
    int left = 0;
    int right = path.size() - 1;

    while (left < right) {
        swapPositions(path[left], path[right]);
        left++;
        right--;
    }
}

vector<Position> PathFinder::findShortestPath(
    vector<vector<char>> grid,
    Position start,
    Position target
) {
    vector<Position> emptyPath;

    if (grid.size() == 0) {
        return emptyPath;
    }

    int rows = grid.size();
    int cols = grid[0].size();

    if (isInsideGrid(start.row, start.col, rows, cols) == false) {
        return emptyPath;
    }

    if (isInsideGrid(target.row, target.col, rows, cols) == false) {
        return emptyPath;
    }

    if (isWalkable(grid[start.row][start.col]) == false) {
        return emptyPath;
    }

    if (isWalkable(grid[target.row][target.col]) == false) {
        return emptyPath;
    }

    queue<Position> q;

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    vector<vector<Position>> parent(
        rows,
        vector<Position>(cols, Position(-1, -1))
    );

    int dRow[4] = {-1, 1, 0, 0};
    int dCol[4] = {0, 0, -1, 1};

    q.push(start);
    visited[start.row][start.col] = true;

    while (q.empty() == false) {
        Position current = q.front();
        q.pop();

        if (current.row == target.row && current.col == target.col) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dRow[i];
            int newCol = current.col + dCol[i];

            bool inside = isInsideGrid(newRow, newCol, rows, cols);

            if (inside == true) {
                bool notVisited = visited[newRow][newCol] == false;
                bool walkable = isWalkable(grid[newRow][newCol]);

                if (notVisited == true && walkable == true) {
                    visited[newRow][newCol] = true;
                    parent[newRow][newCol] = current;
                    q.push(Position(newRow, newCol));
                }
            }
        }
    }

    if (visited[target.row][target.col] == false) {
        return emptyPath;
    }

    vector<Position> path;

    Position current = target;

    while (true) {
        path.push_back(current);

        if (current.row == start.row && current.col == start.col) {
            break;
        }

        current = parent[current.row][current.col];
    }

    reversePath(path);

    return path;
}

int PathFinder::findShortestDistance(
    vector<vector<char>> grid,
    Position start,
    Position target
) {
    vector<Position> path = findShortestPath(grid, start, target);

    if (path.size() == 0) {
        return -1;
    }

    int distance = path.size() - 1;

    return distance;
}
