#include <iostream>
using namespace std;

struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void find_completion_time(Process proc[], int n){
    proc[0].ct = proc[0].bt;
    for (int i=1; i<n; i++){
        proc[i].ct = proc[i-1].ct + proc[i].bt;
    }
}

void find_turn_around_time(Process proc[], int n){
    for (int i=0; i<n; i++){
        proc[i].tat = proc[i].ct - proc[i].at;
    }
}

void find_waiting_time(Process proc[], int n){
    for (int i=0; i<n; i++){
        proc[i].wt = proc[i].tat - proc[i].bt;
    }
}

void FCFS(Process proc[], int n){
    find_completion_time(proc, n);
    find_turn_around_time(proc, n);
    find_waiting_time(proc, n);
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i=0; i<n; i++){
        cout << proc[i].pid << "\t" << proc[i].at << "\t" << proc[i].bt << "\t" << proc[i].ct << "\t" << proc[i].tat << "\t" << proc[i].wt << "\n";
    }
}

void gantt_chart(Process proc[], int n) {
    // Bubble Sort to order processes by pid in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].pid > proc[j + 1].pid) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    // Display the Gantt Chart
    cout << "Gantt Chart:" << endl;
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << " ";
    }
    cout << endl;
}

int main(){
    Process proc[5] = {{1,0,5},{2,1,3},{3,2,2},{4,3,4},{5,4,1}};
    FCFS(proc, 5);
    gantt_chart(proc, 5);
    return 0;
}