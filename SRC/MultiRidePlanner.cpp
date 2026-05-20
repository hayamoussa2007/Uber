#include "MultiRidePlanner.h"
#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;

int MultiRidePlanner::manhattan(Position a, Position b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

int MultiRidePlanner::solve(
    int requestIndex,
    int usedMask,
    const vector<Driver>& drivers,
    const vector<RideRequest>& requests,
    vector<vector<int>>& dp
) {
    if (requestIndex == requests.size()) {
        return 0;
    }

    if (dp[requestIndex][usedMask] != -1) {
        return dp[requestIndex][usedMask];
    }

    int bestCost = INT_MAX;

    for (int i = 0; i < drivers.size(); i++) {
        if (usedMask & (1 << i)) {
            continue;
        }

        if (!drivers[i].available) {
            continue;
        }

        int cost = manhattan(drivers[i].location, requests[requestIndex].pickup);

        int futureCost = solve(
            requestIndex + 1,
            usedMask | (1 << i),
            drivers,
            requests,
            dp
        );

        if (futureCost != INT_MAX && cost + futureCost < bestCost) {
            bestCost = cost + futureCost;
        }
    }

    dp[requestIndex][usedMask] = bestCost;

    return bestCost;
}

int MultiRidePlanner::findMinimumAssignmentCost(
    const vector<Driver>& drivers,
    const vector<RideRequest>& requests
) {
    if (drivers.size() < requests.size()) {
        return -1;
    }

    int maxMask = 1 << drivers.size();

    vector<vector<int>> dp(
        requests.size(),
        vector<int>(maxMask, -1)
    );

    int result = solve(0, 0, drivers, requests, dp);

    if (result == INT_MAX) {
        return -1;
    }

    return result;
}

vector<int> MultiRidePlanner::assignDriversToRequests(
    const vector<Driver>& drivers,
    const vector<RideRequest>& requests
) {
    vector<int> assignment;

    if (drivers.size() < requests.size()) {
        return assignment;
    }

    int maxMask = 1 << drivers.size();

    vector<vector<int>> dp(
        requests.size(),
        vector<int>(maxMask, -1)
    );

    int minimumCost = solve(0, 0, drivers, requests, dp);

    if (minimumCost == INT_MAX) {
        return assignment;
    }

    int usedMask = 0;

    for (int requestIndex = 0; requestIndex < requests.size(); requestIndex++) {
        int bestDriver = -1;
        int bestCost = INT_MAX;

        for (int i = 0; i < drivers.size(); i++) {
            if (usedMask & (1 << i)) {
                continue;
            }

            if (!drivers[i].available) {
                continue;
            }

            int pickupCost = manhattan(drivers[i].location, requests[requestIndex].pickup);

            int futureCost;

            if (requestIndex + 1 == requests.size()) {
                futureCost = 0;
            } else {
                futureCost = dp[requestIndex + 1][usedMask | (1 << i)];
            }

            if (futureCost != -1 && futureCost != INT_MAX) {
                int totalCost = pickupCost + futureCost;

                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestDriver = i;
                }
            }
        }

        if (bestDriver == -1) {
            assignment.clear();
            return assignment;
        }

        assignment.push_back(bestDriver);
        usedMask = usedMask | (1 << bestDriver);
    }

    return assignment;
}

void MultiRidePlanner::optimizeAssignments(
    const vector<RideRequest>& requests,
    const vector<Driver>& drivers
) {
    cout << "\nMULTI-RIDE DP ASSIGNMENT RESULT" << endl;

    int minimumCost = findMinimumAssignmentCost(drivers, requests);

    if (minimumCost == -1) {
        cout << "No valid assignment possible." << endl;
        return;
    }

    vector<int> assignment = assignDriversToRequests(drivers, requests);

    if (assignment.empty()) {
        cout << "No valid assignment possible." << endl;
        return;
    }

    int totalTripDistance = 0;

    for (int i = 0; i < requests.size(); i++) {
        int driverIndex = assignment[i];

        Driver selectedDriver = drivers[driverIndex];
        RideRequest request = requests[i];

        int driverToPickup = manhattan(selectedDriver.location, request.pickup);
        int pickupToDestination = manhattan(request.pickup, request.destination);
        int tripDistance = driverToPickup + pickupToDestination;

        totalTripDistance += tripDistance;

        cout << "Request ID: R" << request.id << endl;
        cout << "Assigned Driver: D" << selectedDriver.id << endl;
        cout << "Driver to Pickup Distance: " << driverToPickup << endl;
        cout << "Pickup to Destination Distance: " << pickupToDestination << endl;
        cout << "Trip Total Distance: " << tripDistance << endl;
        cout << "--------------------------------------------" << endl;
    }

    cout << "Minimum Assignment Cost: " << minimumCost << endl;
    cout << "Grand Total Trip Distance: " << totalTripDistance << endl;
}