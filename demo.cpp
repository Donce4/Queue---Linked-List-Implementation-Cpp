#include <iostream>
#include "queue.h"

using namespace MyDataStructure;

int main()
{
    std::cout << "--- Starting Queue Demonstration ---\n";

    // Constructor & enqueue
    Queue q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    std::cout << "q1 after enqueues: " << q1.toString();

    // operator+=
    q1 += 40;
    std::cout << "q1 after += 40: " << q1.toString();

    // dequeue
    int removed = q1.dequeue();
    std::cout << "Dequeued value: " << removed << "\n";
    std::cout << "q1 after dequeue: " << q1.toString();

    // operator-=
    q1 -= 1;
    std::cout << "q1 after -= 1: " << q1.toString();

    // operator*=
    q1 *= 2;
    std::cout << "q1 after *= 2: " << q1.toString();

    // operator[]
    try
    {
        int pos = q1[80];
        std::cout << "Position of value 80: " << pos << "\n";
    }
    catch (const QueueException &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    // Copy Constructor & Assignment
    Queue q2 = q1; // Copy constructor
    Queue q3;
    q3 = q1; // Assignment operator
    q3 += 100;

    std::cout << "\nq2 (copy of q1): " << q2.toString();
    std::cout << "q3 (assigned from q1, added 100): " << q3.toString();

    // Comparison Operators
    std::cout << "\n--- Comparisons ---\n";
    std::cout << "q1 == q2: " << (q1 == q2 ? "true" : "false") << "\n";
    std::cout << "q1 != q3: " << (q1 != q3 ? "true" : "false") << "\n";
    std::cout << "q1 < q3: " << (q1 < q3 ? "true" : "false") << "\n";
    std::cout << "q3 > q1: " << (q3 > q1 ? "true" : "false") << "\n";
    std::cout << "q1 <= q2: " << (q1 <= q2 ? "true" : "false") << "\n";
    std::cout << "q3 >= q1: " << (q3 >= q1 ? "true" : "false") << "\n";

    // operator! and isEmpty
    !q1;
    std::cout << "\nq1 after ! (clear): " << q1.toString();
    std::cout << "q1 isEmpty(): " << (q1.isEmpty() ? "true" : "false") << "\n";

    std::cout << "--- Demonstration Complete ---\n";
    return 0;
}