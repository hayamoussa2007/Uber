#ifndef DRIVERMATCHER_H
#define DRIVERMATCHER_H

#include <iostream>
#include <vector>
#include "Position.h"
#include "Driver.h"

using namespace std;

class DriverMatcher {
public:
    // Calculates Manhattan (grid) distance between two positions
    static int manhattanDistance(Position a, Position b);

    // Divides the grid into 4 quadrants and returns which one p falls in
    // Region 1 = top-left, 2 = top-right, 3 = bottom-left, 4 = bottom-right
    static int getRegion(Position p, int rows, int cols);

    // Returns all available drivers located in the given region
    static vector<Driver> getDriversInRegion(
        const vector<Driver>& drivers,
        int region,
        int rows,
        int cols
    );

    // Greedy: picks the available driver with smallest Manhattan distance to pickup
    static Driver chooseNearestDriver(
        const vector<Driver>& drivers,
        Position pickup
    );

    // Divide & Conquer + Greedy:
    // Search same region first; fall back to all drivers if region is empty
    static Driver chooseDriverByRegion(
        const vector<Driver>& drivers,
        Position pickup,
        int rows,
        int cols
    );
};

#endif
