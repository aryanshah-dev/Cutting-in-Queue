// Cutting_In_Queue_Lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Job {
private:
    string name;
    int priority;

public:
    Job(string n, int p) : name(n), priority(p) {}

    void execute() {
        cout << "Running job: " << name
            << " (Priority: " << priority << ")" << endl;
    }

    string getName() {
        return name;
    }

    int getPriority() {
        return priority;
    }

    bool operator<(const Job& other) const {
        return priority < other.priority;
    }
};

template <typename T>
class MaxHeap {
private:
    vector<T> heap;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (!(heap[parent] < heap[index])) {
                break;
            }

            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void siftDown(int index) {
        int size = static_cast<int>(heap.size());

        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[largest] < heap[left]) {
                largest = left;
            }

            if (right < size && heap[largest] < heap[right]) {
                largest = right;
            }

            if (largest == index) {
                break;
            }

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    void insert(const T& value) {
        heap.push_back(value);
        siftUp(static_cast<int>(heap.size()) - 1);
    }

    T removeMax() {
        T highest = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            siftDown(0);
        }

        return highest;
    }

    bool empty() const {
        return heap.empty();
    }
};

template <typename T>
class PriorityQueue {
private:
    MaxHeap<T> heap;

public:
    void insert(const T& value) {
        heap.insert(value);
    }

    T removeMax() {
        return heap.removeMax();
    }

    bool empty() const {
        return heap.empty();
    }
};

class JobQueue {
private:
    PriorityQueue<Job> jobs;

public:
    void insert(Job job) {
        jobs.insert(job);
    }

    void runHighestPriority() {
        if (jobs.empty()) {
            return;
        }

        Job job = jobs.removeMax();
        job.execute();
    }
};

int main() {
    JobQueue jobQueue;

    Job jobA("This is job a", 5);
    Job jobB("This is job b", 2);
    Job jobC("This is job c", 9);
    Job jobD("This is job d", 8);
    Job jobE("This is job e", 1);

    jobQueue.insert(jobA);
    jobQueue.insert(jobB);
    jobQueue.insert(jobC);
    jobQueue.insert(jobD);
    jobQueue.insert(jobE);

    jobQueue.runHighestPriority();
    jobQueue.runHighestPriority();
    jobQueue.runHighestPriority();
    jobQueue.runHighestPriority();
    jobQueue.runHighestPriority();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
