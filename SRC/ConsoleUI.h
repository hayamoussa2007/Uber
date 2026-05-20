#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <vector>
#include <iostream>

#include "CityGrid.h"
#include "Driver.h"
#include "RideRequest.h"
#include "Position.h"
#include "PathFinder.h"
#include "DriverMatcher.h"
#include "TripCalculator.h"

using namespace std;

class ConsoleUI {
private:
    CityGrid cityGrid;
    vector<Driver> drivers;
    RideRequest currentRequest;

public:
    ConsoleUI(int rows, int cols);
    void run();

private:
    void showMenu();
    void handleDisplayGrid();
    void handleAddDriver();
    void handleAddBlockedCell();
    void handleSetPickup();
    void handleSetDestination();
    void handleFindRide();
    void handleRunSmallDemo();
    void handleRunLargePdfCase();
    void handleResetGrid();
    void handleRunBlockedPathCase();
    void handleRunMultiRequestCase();
    Position readPosition();
};

#endif
