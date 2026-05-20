#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

#include "Position.h"

struct RideRequest {
    int id;
    Position pickup;
    Position destination;

    RideRequest() : id(-1), pickup(Position()), destination(Position()) {}

    RideRequest(int requestId, Position p, Position d)
        : id(requestId), pickup(p), destination(d) {}
};

#endif