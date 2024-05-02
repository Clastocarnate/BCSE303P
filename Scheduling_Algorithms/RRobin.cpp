#include<iostream>
#include<vector>

struct Process {
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateTimes(Process processes[], int n, int quantum) {
    std::vector<int> remainingTime(n);
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    bool allDone = false;
    
    while (!allDone) {
        allDone = true;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                allDone = false;
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    currentTime += remainingTime[i];
                    processes[i].waitingTime = currentTime - processes[i].burstTime;
                    remainingTime[i] = 0;
                }
            }
        }
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void calculateAverageTimes(Process processes[], int n, int quantum) {
    calculateTimes(processes, n, quantum);
    calculateTurnaroundTime(processes, n);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    std::cout << "Average Waiting Time = " 
              << (float)totalWaitingTime / (float)n << std::endl;
    std::cout << "Average Turnaround Time = " 
              << (float)totalTurnaroundTime / (float)n << std::endl;
}

int main() {
    int n, quantum;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;
    Process processes[n];

    for (int i = 0; i < n; i++) {
        std::cout << "Enter burst time for process " << i + 1 << ": ";
        std::cin >> processes[i].burstTime;
    }

    std::cout << "Enter quantum time: ";
    std::cin >> quantum;

    calculateAverageTimes(processes, n, quantum);

    return 0;
}
