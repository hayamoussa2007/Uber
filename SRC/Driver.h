#ifndef DRIVER_H
#define DRIVER_H

#include "Position.h"

struct Driver {
    int id;
    Position location;
    bool available;

    Driver() : id(-1), location(Position()), available(true) {}

    Driver(int driverId, Position driverLocation)
        : id(driverId), location(driverLocation), available(true) {}
};

#endif