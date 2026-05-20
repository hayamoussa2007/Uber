#include "DriverMatcher.h"
#include <cstdlib>
#include <climits>

using namespace std;

// ─────────────────────────────────────────────
// manhattanDistance
// Formula: |row1 - row2| + |col1 - col2|
// ─────────────────────────────────────────────
int DriverMatcher::manhattanDistance(Position a, Position b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

// ─────────────────────────────────────────────
// getRegion  (Divide & Conquer — split into 4)
//   1 = top-left  | 2 = top-right
//   3 = bot-left  | 4 = bot-right
// ─────────────────────────────────────────────
int DriverMatcher::getRegion(Position p, int rows, int cols) {
    bool topHalf  = p.row < rows / 2;
    bool leftHalf = p.col < cols / 2;

    if ( topHalf &&  leftHalf) return 1;
    if ( topHalf && !leftHalf) return 2;
    if (!topHalf &&  leftHalf) return 3;
    return 4;
}

// ─────────────────────────────────────────────
// getDriversInRegion
// Filters the driver list to only those in the
// requested region AND marked available.
// ─────────────────────────────────────────────
vector<Driver> DriverMatcher::getDriversInRegion(
    const vector<Driver>& drivers,
    int region,
    int rows,
    int cols
) {
    vector<Driver> result;

    for (const Driver& driver : drivers) {
        if (!driver.available) continue;

        int driverRegion = getRegion(driver.location, rows, cols);

        if (driverRegion == region) {
            result.push_back(driver);
        }
    }

    return result;
}

// ─────────────────────────────────────────────
// chooseNearestDriver  (Greedy)
// Scans all available drivers and keeps the one
// with the smallest Manhattan distance so far.
// ─────────────────────────────────────────────
Driver DriverMatcher::chooseNearestDriver(
    const vector<Driver>& drivers,
    Position pickup
) {
    Driver bestDriver;
    int bestDistance = INT_MAX;

    for (const Driver& driver : drivers) {
        if (!driver.available) continue;

        int distance = manhattanDistance(driver.location, pickup);

        if (distance < bestDistance) {
            bestDistance = distance;
            bestDriver   = driver;
        }
    }

    return bestDriver;
}

// ─────────────────────────────────────────────
// chooseDriverByRegion  (D&C + Greedy combined)
// 1. Find pickup's region.
// 2. Get available drivers in that region.
// 3. If any exist → greedy pick from them.
// 4. Otherwise   → greedy pick from ALL drivers.
// ─────────────────────────────────────────────
Driver DriverMatcher::chooseDriverByRegion(
    const vector<Driver>& drivers,
    Position pickup,
    int rows,
    int cols
) {
    int pickupRegion = getRegion(pickup, rows, cols);

    vector<Driver> nearbyDrivers = getDriversInRegion(
        drivers, pickupRegion, rows, cols
    );

    if (!nearbyDrivers.empty()) {
        return chooseNearestDriver(nearbyDrivers, pickup);
    }

    return chooseNearestDriver(drivers, pickup);
}
