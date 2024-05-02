#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Function to calculate page faults using FIFO page replacement algorithm
int fifoPageReplacement(vector<int> refString, int frames) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : refString) {
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            pageFaults++;
            if (memory.size() == frames) {
                memory.erase(memory.begin());  // Remove the oldest (first) element
            }
            memory.push_back(page);
        }
    }
    return pageFaults;
}

// Function to calculate page faults using LRU page replacement algorithm
int lruPageReplacement(vector<int> refString, int frames) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : refString) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            pageFaults++;
            if (memory.size() == frames) {
                memory.erase(memory.begin());  // Remove least recently used
            }
        } else {
            memory.erase(it);  // Move the recently used page to the back
        }
        memory.push_back(page);
    }
    return pageFaults;
}

// Function to calculate page faults using Optimal page replacement algorithm
int optimalPageReplacement(vector<int> refString, int frames) {
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < refString.size(); i++) {
        int page = refString[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            pageFaults++;
            if (memory.size() == frames) {
                // Find the optimal page to remove
                int mostDistant = -1, idx = -1;
                for (int j = 0; j < memory.size(); j++) {
                    int k;
                    for (k = i + 1; k < refString.size(); k++) {
                        if (memory[j] == refString[k]) break;
                    }
                    if (k > mostDistant) {
                        mostDistant = k;
                        idx = j;
                    }
                }
                if (idx == -1) idx = 0;  // If no such page is found
                memory.erase(memory.begin() + idx);
            }
            memory.push_back(page);
        }
    }
    return pageFaults;
}

int main() {
    vector<int> referenceString = {6, 1, 1, 2, 0, 3, 4, 6, 0, 2, 1, 2, 1, 2, 0, 3, 2, 1, 4, 0};
    int frames = 3;

    cout << "FIFO Page Faults: " << fifoPageReplacement(referenceString, frames) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(referenceString, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(referenceString, frames) << endl;

    return 0;
}
