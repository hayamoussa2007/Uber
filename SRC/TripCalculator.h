#ifndef TRIPCALCULATOR_H
#define TRIPCALCULATOR_H

#include <iostream>
#include <vector>

#include "Position.h"
#include "TripResult.h"

using namespace std;

class TripCalculator {
public:
    static double calculateTime(int totalDistance);

    static double calculateCost(int totalDistance);

    static TripResult buildTripResult(
        int requestId,
        int driverId,
        int driverToPickupDistance,
        int pickupToDestinationDistance,
        const vector<Position>& driverToPickupPath,
        const vector<Position>& pickupToDestinationPath
    );

    static void printTripResult(const TripResult& result);
};

#endif
