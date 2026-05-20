#include "TripCalculator.h"

using namespace std;

double TripCalculator::calculateTime(int totalDistance) {
    return totalDistance * 2;
}

double TripCalculator::calculateCost(int totalDistance) {
    return totalDistance * 5;
}

TripResult TripCalculator::buildTripResult(
    int requestId,
    int driverId,
    int driverToPickupDistance,
    int pickupToDestinationDistance,
    const vector<Position>& driverToPickupPath,
    const vector<Position>& pickupToDestinationPath
) {
    TripResult result;

    if (driverToPickupDistance < 0 || pickupToDestinationDistance < 0) {
        result.success = false;
        return result;
    }

    result.requestId = requestId;
    result.driverId = driverId;
    result.driverToPickupDistance = driverToPickupDistance;
    result.pickupToDestinationDistance = pickupToDestinationDistance;
    result.totalDistance = driverToPickupDistance + pickupToDestinationDistance;

    result.estimatedTime = calculateTime(result.totalDistance);
    result.cost = calculateCost(result.totalDistance);
    result.success = true;

    result.fullPath = driverToPickupPath;

    for (int i = 1; i < pickupToDestinationPath.size(); i++) {
        result.fullPath.push_back(pickupToDestinationPath[i]);
    }

    return result;
}

void TripCalculator::printTripResult(const TripResult& result) {
    if (!result.success) {
        cout << "\n------------------------------" << endl;
        cout << "Trip Failed" << endl;
        cout << "------------------------------" << endl;
        cout << "No valid route found." << endl;
        return;
    }

    cout << "\n------------------------------" << endl;
    cout << "Trip Details" << endl;
    cout << "------------------------------" << endl;
    cout << "Request: R" << result.requestId << endl;
    cout << "Driver: D" << result.driverId << endl;
    cout << "Driver to Pickup Distance: "
         << result.driverToPickupDistance << endl;
    cout << "Pickup to Destination Distance: "
         << result.pickupToDestinationDistance << endl;
    cout << "Total Distance: " << result.totalDistance << endl;
    cout << "Estimated Time: " << result.estimatedTime << " minutes" << endl;
    cout << "Cost: " << result.cost << " EGP" << endl;
    cout << "------------------------------" << endl;
}