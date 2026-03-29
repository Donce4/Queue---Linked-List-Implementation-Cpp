#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace MyDataStructure;

void runTest(bool condition, const std::string &testName, std::ofstream &log)
{
    std::string result = condition ? "PASSED" : "FAILED";
    std::string output = "Test [" + testName + "]: " + result + "\n";
    std::cout << output;
    log << output;
}

void logMessage(const std::string &msg, std::ofstream &log)
{
    std::cout << msg << "\n";
    log << msg << "\n";
}

int main()
{
    std::ofstream logFile("log.txt");
    if (!logFile)
    {
        std::cerr << "Error: Could not open log.txt\n";
        return 1;
    }

    logMessage("--- Starting Queue Diagnostic Tests ---", logFile);

    Queue q1;

    // 1. Basic State & Enqueue Tests
    logMessage("\n[Phase 1: Basic Operations]", logFile);
    runTest(q1.isEmpty() == true, "New queue is empty", logFile);
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    runTest(q1.isEmpty() == false, "Queue not empty after enqueues", logFile);

    // 2. Search & Indexing (operator[])
    logMessage("\n[Phase 2: Search by Value]", logFile);
    runTest(q1[10] == 0, "Find value 10 at index 0", logFile);
    runTest(q1[30] == 2, "Find value 30 at index 2", logFile);

    bool caughtNotFound = false;
    try
    {
        q1[99]; // Should throw QueueException
    }
    catch (const QueueException &e)
    {
        caughtNotFound = true;
    }
    runTest(caughtNotFound, "Exception thrown for missing value", logFile);

    // 3. Dequeue & Removal
    logMessage("\n[Phase 3: Dequeue and Removal]", logFile);
    runTest(q1.dequeue() == 10, "Dequeue returns front value (10)", logFile);
    q1 -= 1; // Removes the next item (20)
    runTest(q1[30] == 0, "Value 30 is now at index 0 after -= operator", logFile);

    // 4. Mathematical Operators
    logMessage("\n[Phase 4: Mathematical Operators]", logFile);
    q1 += 40; // Queue is now [30, 40]
    q1 *= 2;  // Queue is now [60, 80]
    runTest(q1[60] == 0 && q1[80] == 1, "Operator *= correctly multiplies elements", logFile);

    // 5. Deep Copy & Comparisons
    logMessage("\n[Phase 5: Copying and Comparisons]", logFile);
    Queue q2 = q1;
    runTest(q1 == q2, "Copied queue is equal (operator==)", logFile);
    q2 += 100;
    runTest(q1 != q2, "Modified copy is not equal (operator!=)", logFile);
    runTest(q1 < q2, "Original queue is less than modified copy (operator<)", logFile);

    // 6. Clean / Empty Object
    logMessage("\n[Phase 6: Object Cleaning]", logFile);
    !q2;
    runTest(q2.isEmpty() == true, "Operator! successfully empties the queue", logFile);

    // 7. Underflow Exception
    logMessage("\n[Phase 7: Underflow Handling]", logFile);
    bool caughtUnderflow = false;
    try
    {
        q2.dequeue(); // Should throw since q2 is empty
    }
    catch (const QueueException &e)
    {
        caughtUnderflow = true;
    }
    runTest(caughtUnderflow, "Exception thrown on empty dequeue", logFile);

    logMessage("\n--- Diagnostic Tests Complete ---", logFile);
    logFile.close();
    return 0;
}