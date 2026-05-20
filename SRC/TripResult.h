#ifndef TRIPRESULT_H
#define TRIPRESULT_H

#include <vector>
#include "Position.h"

struct TripResult {
    int requestId;
    int driverId;

    int driverToPickupDistance;
    int pickupToDestinationDistance;
    int totalDistance;

    double estimatedTime;
    double cost;

    bool success;
    std::vector<Position> fullPath;

    TripResult()
        : requestId(-1),
          driverId(-1),
          driverToPickupDistance(-1),
          pickupToDestinationDistance(-1),
          totalDistance(-1),
          estimatedTime(0),
          cost(0),
          success(false) {}
};

#endif