#ifndef TESTCASES_H
#define TESTCASES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Note: TestCases is usually a collection of static functions
// so you don't need to create an object to run them.
class TestCases {
public:
    // 1. A small 10x10 case that is easy to display
    static void runSmallDemoCase();

    // 2. A case where BFS must go around obstacles
    static void runBlockedPathCase();

    // 3. A case where the destination is fully unreachable
    static void runNoPathCase();

    // 4. The 500x500 grid stress test from the PDF
    static void runLargePdfCase();

    // 5. Calls the DP module for multi-request optimization
    static void runMultiRequestCase();

private:
    // Helper to print a header for each test to the console
    static void printTestHeader(const string& testName);
    // static is used to be able to directly use functions in the class without having to create objects
};

#endif