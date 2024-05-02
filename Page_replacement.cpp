#include <iostream>
using namespace std;

const int MAX = 100; // Assuming a maximum reference string length

// Function to calculate page faults using FIFO page replacement algorithm
int fifoPageReplacement(int refString[], int n, int frames) {
    int memory[frames], pageFaults = 0, index = 0;
    fill(memory, memory + frames, -1); // Initialize memory slots to -1

    for (int i = 0; i < n; i++) {
        int page = refString[i];
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = true;
                break;
            }
        }
        if (!found) {
            pageFaults++;
            memory[index] = page;
            index = (index + 1) % frames; // Move index in a circular manner
        }
    }
    return pageFaults;
}

// Function to calculate page faults using LRU page replacement algorithm
int lruPageReplacement(int refString[], int n, int frames) {
    int memory[frames], pageFaults = 0;
    int lastUsed[frames];
    fill(memory, memory + frames, -1); // Initialize memory slots to -1

    for (int i = 0; i < n; i++) {
        int page = refString[i];
        int leastRecentlyUsed = i, lruIndex = -1;
        bool found = false;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = true;
                lastUsed[j] = i; // Update last used time
                break;
            }
        }
        if (!found) {
            pageFaults++;
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1 || lastUsed[j] < leastRecentlyUsed) {
                    leastRecentlyUsed = lastUsed[j];
                    lruIndex = j;
                }
            }
            memory[lruIndex] = page;
            lastUsed[lruIndex] = i; // Update last used time for the new page
        }
    }
    return pageFaults;
}

// Function to calculate page faults using Optimal page replacement algorithm
int optimalPageReplacement(int refString[], int n, int frames) {
    int memory[frames], pageFaults = 0;
    fill(memory, memory + frames, -1); // Initialize memory slots to -1

    for (int i = 0; i < n; i++) {
        int page = refString[i];
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = true;
                break;
            }
        }
        if (!found) {
            pageFaults++;
            int optIndex = -1, farthest = i;
            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (memory[j] == refString[k]) {
                        if (k > farthest) {
                            farthest = k;
                            optIndex = j;
                        }
                        break;
                    }
                }
                if (k == n) { // If no such page is found in future
                    optIndex = j;
                    break;
                }
            }
            if (optIndex == -1) optIndex = 0;
            memory[optIndex] = page;
        }
    }
    return pageFaults;
}

int main() {
    int referenceString[MAX] = {6, 1, 1, 2, 0, 3, 4, 6, 0, 2, 1, 2, 1, 2, 0, 3, 2, 1, 4, 0};
    int n = 20; // Length of the reference string
    int frames = 3;

    cout << "FIFO Page Faults: " << fifoPageReplacement(referenceString, n, frames) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(referenceString, n, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(referenceString, n, frames) << endl;

    return 0;
}
