#include <iostream>
#include <stdexcept>
#include <sstream>
#include "queue.h"

namespace MyDataStructure
{
    class Queue::QueueImpl
    {
        struct Node
        {
            int data;
            Node *next;
            Node(int new_data) : data(new_data), next(nullptr) {}
        };

        Node *front;
        Node *rear;
        int count;

    public:
        QueueImpl()
        {
            front = nullptr;
            rear = nullptr;
            count = 0;
        }

        QueueImpl(const QueueImpl &other)
        {
            front = nullptr;
            rear = nullptr;
            count = 0;

            Node *current = other.front;
            while (current != nullptr)
            {
                enqueue(current->data);
                current = current->next;
            }
        }

        ~QueueImpl()
        {
            while (front)
            {
                Node *tmp = front->next;
                delete front;
                front = tmp;
            }
        }

        bool isEmpty() const
        {
            return front == nullptr;
        }
        int getCount() const
        {
            return count;
        }

        void enqueue(int new_data)
        {
            Node *node = new Node(new_data);
            if (isEmpty())
            {
                front = rear = node;
            }
            else
            {
                rear->next = node;
                rear = node;
            }
            ++count;
        }

        int dequeue()
        {
            if (isEmpty())
                throw QueueException("Queue underflow");
            Node *temp = front;
            int removeData = temp->data;
            front = front->next;
            if (front == nullptr)
                rear = nullptr;
            delete temp;
            count--;
            return removeData;
        }

        void multiplyAll(int factor)
        {
            Node *curr = front;
            while (curr)
            {
                curr->data *= factor;
                curr = curr->next;
            }
        }

        int indexSearch(int target_value) const
        {
            Node *curr = front;
            int index = 0;
            while (curr)
            {
                if (curr->data == target_value)
                    return index;
                curr = curr->next;
                ++index;
            }
            return -1;
        }

        int compare(const Queue &other) const
        {
            Node *curr1 = this->front;
            Node *curr2 = other.impl->front;
            while (curr1 && curr2)
            {
                if (curr1->data > curr2->data)
                    return 1;
                if (curr1->data < curr2->data)
                    return -1;
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
            if (curr1)
                return 1;
            if (curr2)
                return -1;
            return 0;
        }

        bool isEqual(const Queue &obj) const
        {
            if (obj.impl->count != count)
                return false;
            Node *curr1 = obj.impl->front;
            Node *curr2 = front;
            while (curr1 && curr2)
            {
                if (curr1->data != curr2->data)
                    return false;
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
            return true;
        }

        std::string toString() const
        {
            std::stringstream ss;
            ss << "Queue: [";

            Node *curr = front;
            int displayCount = 0;
            const int MAX_DISPLAY = 5; // Top Key limit
            
            while (curr && displayCount < MAX_DISPLAY)
            {
                ss << curr->data;
                curr = curr->next;
                displayCount++;

                if (curr && displayCount < MAX_DISPLAY)
                {
                    ss << ", ";
                }
            }

            if (curr)
            {
                ss << "...";
            }

            ss << "] Node count: " << count;
            return ss.str();
        }
    };

    Queue::Queue()
        : impl(new QueueImpl()) {}

    Queue::~Queue()
    {
        delete impl;
    }

    Queue::Queue(const Queue &obj)
        : impl(new QueueImpl(*obj.impl)) {}

    Queue &Queue::operator=(const Queue &obj)
    {
        if (this != &obj)
        {
            QueueImpl *newImpl = new QueueImpl(*obj.impl);
            delete impl;
            impl = newImpl;
        }
        return *this;
    }

    QueueException::QueueException(const std::string &message)
        : std::runtime_error(message) {}

    void Queue::enqueue(int new_data)
    {
        impl->enqueue(new_data);
    }
    int Queue::dequeue()
    {
        return impl->dequeue();
    }
    bool Queue::isEmpty() const
    {
        return impl->isEmpty();
    }
    std::string Queue::toString() const
    {
        return impl->toString();
    }

    Queue &Queue::operator+=(int new_data)
    {
        impl->enqueue(new_data);
        return *this;
    }
    Queue &Queue::operator*=(int factor)
    {
        impl->multiplyAll(factor);
        return *this;
    }
    Queue &Queue::operator!()
    {
        while (!isEmpty())
            dequeue();
        return *this;
    }

    Queue &Queue::operator-=(int count_to_remove)
    {
        if (impl->getCount() < count_to_remove)
            throw QueueException("Removal count exceeds size");
        while (count_to_remove--)
            dequeue();
        return *this;
    }

    int Queue::operator[](int target_value) const
    {
        int pos = impl->indexSearch(target_value);
        if (pos == -1)
            throw QueueException("Value not found");
        return pos;
    }

    bool Queue::operator==(const Queue &obj) const
    {
        return impl->isEqual(obj);
    }
    bool Queue::operator!=(const Queue &obj) const
    {
        return !(*this == obj);
    }
    bool Queue::operator<(const Queue &obj) const
    {
        return impl->compare(obj) == -1;
    }
    bool Queue::operator>(const Queue &obj) const
    {
        return impl->compare(obj) == 1;
    }
    bool Queue::operator<=(const Queue &obj) const
    {
        return impl->compare(obj) <= 0;
    }
    bool Queue::operator>=(const Queue &obj) const
    {
        return impl->compare(obj) >= 0;
    }
}