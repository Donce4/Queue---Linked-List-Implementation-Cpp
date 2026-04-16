/**
 * class Queue
 * First-In-First-Out (FIFO) Queue Abstract Data Type.
 *
 * This class implements a dynamic queue using the Pimpl (Pointer to Implementation) idiom
 *
 * Key Features & Operations:
 * - Memory Management: Implements deep copying and RAII principles
 * - Insertion/Deletion: operator+= enqueues an element; operator-= dequeues a specified number of elements.
 * - Editing: operator*= multiplies all elements in the queue by a given factor.
 * - State Management: operator! completely clears all elements from the queue.
 * - Search: operator[] searches for a specific target value and returns its zero-based index position.
 * - Comparisons: Fully supports logically aligned relational operators (==, !=, <, >, <=, >=).
 * - Output: toString() returns a formatted string containing the queue's elements and total count.
 *
 * throws QueueException Custom exception thrown on queue underflow (dequeueing an empty queue),
 * attempting to remove too many elements, or searching for a non-existent value.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <string>

namespace MyDataStructure
{

    class QueueException : public std::runtime_error
    {
    public:
        explicit QueueException(const std::string &message);
    };

    class Queue
    {
    private:
        class QueueImpl;
        QueueImpl *impl;
    public:
        Queue();
        ~Queue();
        Queue(const Queue &obj);
        Queue &operator=(const Queue &obj);

        void enqueue(int new_data);
        int dequeue();
        bool isEmpty() const;
        std::string toString() const;

        Queue &operator+=(int new_data);
        Queue &operator-=(int count_to_remove);
        Queue &operator*=(int factor);
        Queue &operator!();

        int operator[](int target_value) const;

        bool operator==(const Queue &obj) const;
        bool operator!=(const Queue &obj) const;
        bool operator<(const Queue &obj) const;
        bool operator>(const Queue &obj) const;
        bool operator<=(const Queue &obj) const;
        bool operator>=(const Queue &obj) const;
        };

}
#endif