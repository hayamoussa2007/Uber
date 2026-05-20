#include <iostream>
#include "ConsoleUI.h"

using namespace std;

int main() {
    cout << "Starting Smart Uber Ride Matching System..." << endl;

    ConsoleUI app(10, 10);
    app.run();

    return 0;
}
