#ifndef MULTIRIDEPLANNER_H
#define MULTIRIDEPLANNER_H

#include <vector>
#include "Driver.h"
#include "RideRequest.h"
#include "Position.h"

using namespace std;

class MultiRidePlanner {
public:
    static int findMinimumAssignmentCost(
        const vector<Driver>& drivers,
        const vector<RideRequest>& requests
    );

    static vector<int> assignDriversToRequests(
        const vector<Driver>& drivers,
        const vector<RideRequest>& requests
    );

    static void optimizeAssignments(
        const vector<RideRequest>& requests,
        const vector<Driver>& drivers
    );

private:
    static int manhattan(Position a, Position b);

    static int solve(
        int requestIndex,
        int usedMask,
        const vector<Driver>& drivers,
        const vector<RideRequest>& requests,
        vector<vector<int>>& dp
    );
};

#endif