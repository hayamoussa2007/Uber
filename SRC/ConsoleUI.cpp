#include "ConsoleUI.h"
#include "DriverMatcher.h"
#include "PathFinder.h"
#include "TripCalculator.h"
#include "TestCases.h"
#include <iostream>

using namespace std;

ConsoleUI::ConsoleUI(int rows, int cols) : cityGrid(rows, cols) {
    currentRequest = RideRequest();
}

void ConsoleUI::showMenu() {
    cout << "==============================" << endl;
    cout << " Smart Uber Ride Matching" << endl;
    cout << "==============================" << endl;
    cout << "1. Display city grid" << endl;
    cout << "2. Add driver" << endl;
    cout << "3. Add blocked cell" << endl;
    cout << "4. Set pickup point" << endl;
    cout << "5. Set destination" << endl;
    cout << "6. Find best driver and path" << endl;
    cout << "7. Run small demo case" << endl;
    cout << "8. Run large PDF test case" << endl;
    cout << "9. Run blocked path test case" << endl;
    cout << "10. Run multi-request DP test case" << endl;
    cout << "11. Reset grid" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose option: ";
}

void ConsoleUI::run() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                handleDisplayGrid();
                break;

            case 2:
                handleAddDriver();
                break;

            case 3:
                handleAddBlockedCell();
                break;

            case 4:
                handleSetPickup();
                break;

            case 5:
                handleSetDestination();
                break;

            case 6:
                handleFindRide();
                break;

            case 7:
                handleRunSmallDemo();
                break;

            case 8:
                handleRunLargePdfCase();
                break;

            case 9:
                handleRunBlockedPathCase();
                break;

            case 10:
                handleRunMultiRequestCase();
                break;

            case 11:
                handleResetGrid();
                break;

            case 0:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 0);
}

Position ConsoleUI::readPosition() {
    int r, c;

    cout << "Enter row: ";
    cin >> r;

    cout << "Enter column: ";
    cin >> c;

    return Position(r, c);
}

void ConsoleUI::handleDisplayGrid() {
    cityGrid.display();
}

void ConsoleUI::handleAddDriver() {
    Position p = readPosition();

    int newId = drivers.size() + 1;

    drivers.push_back(Driver(newId, p));
    cityGrid.addDriver(p);

    cout << "Driver D" << newId << " added at ("
         << p.row << "," << p.col << ")." << endl;
}

void ConsoleUI::handleAddBlockedCell() {
    Position p = readPosition();

    cityGrid.addBlockedCell(p);

    cout << "Blocked cell added at ("
         << p.row << "," << p.col << ")." << endl;
}

void ConsoleUI::handleSetPickup() {
    Position p = readPosition();

    currentRequest.id = 1;
    currentRequest.pickup = p;

    cityGrid.setPickup(p);

    cout << "Pickup point set at ("
         << p.row << "," << p.col << ")." << endl;
}

void ConsoleUI::handleSetDestination() {
    Position p = readPosition();

    currentRequest.destination = p;

    cityGrid.setDestination(p);

    cout << "Destination set at ("
         << p.row << "," << p.col << ")." << endl;
}

void ConsoleUI::handleFindRide() {
    if (drivers.empty()) {
        cout << "No drivers available." << endl;
        return;
    }

    if (currentRequest.id == -1) {
        cout << "Pickup point is not set." << endl;
        return;
    }

    Driver selected = DriverMatcher::chooseDriverByRegion(
        drivers,
        currentRequest.pickup,
        cityGrid.getRows(),
        cityGrid.getCols()
    );

    if (selected.id == -1) {
        cout << "No available driver found." << endl;
        return;
    }

    vector<Position> path1 = PathFinder::findShortestPath(
        cityGrid.getCells(),
        selected.location,
        currentRequest.pickup
    );

    vector<Position> path2 = PathFinder::findShortestPath(
        cityGrid.getCells(),
        currentRequest.pickup,
        currentRequest.destination
    );

    int d1 = -1;

    if (!path1.empty()) {
        d1 = path1.size() - 1;
    }

    int d2 = -1;

    if (!path2.empty()) {
        d2 = path2.size() - 1;
    }

    TripResult result = TripCalculator::buildTripResult(
        currentRequest.id,
        selected.id,
        d1,
        d2,
        path1,
        path2
    );

    cityGrid.clearPath();

    if (result.success) {
        cityGrid.markPath(result.fullPath);
        cityGrid.display();
        TripCalculator::printTripResult(result);
    } else {
        cout << "Trip failed: No valid route found." << endl;
    }
}

void ConsoleUI::handleResetGrid() {
    cityGrid = CityGrid(cityGrid.getRows(), cityGrid.getCols());
    drivers.clear();
    currentRequest = RideRequest();

    cout << "Grid reset successfully." << endl;
}
void ConsoleUI::handleRunSmallDemo() {
    TestCases::runSmallDemoCase();
}

void ConsoleUI::handleRunLargePdfCase() {
    TestCases::runLargePdfCase();
}
void ConsoleUI::handleRunBlockedPathCase() {
    TestCases::runBlockedPathCase();
}

void ConsoleUI::handleRunMultiRequestCase() {
    TestCases::runMultiRequestCase();
}
