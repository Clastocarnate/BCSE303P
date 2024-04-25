#include <iostream>
using namespace std;

struct Process{
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

void SJB(Process proc[], int n){
    int remaining[n];
    for (int i=0; i<n; i++){
        remaining[i] = proc[i].BT;
    }

    int complete = 0;
    int currentTime = 0;
    int shortest = 0;
    int min = 9999;

    while (complete<n){
        min = 9999;
        for(int i=0; i<n; i++){
            if (proc[i].AT<=currentTime && remaining[i]<min && remaining[i]>0){
                min = remaining[i];
                shortest = i;
            }
        }
            remaining[shortest]--;
           
            if (remaining[shortest] == 0){
                complete++;
                proc[shortest].CT = currentTime + 1;
                proc[shortest].TAT = proc[shortest].CT - proc[shortest].AT;
                proc[shortest].WT = proc[shortest].TAT - proc[shortest].BT;
            }
             currentTime++;
        
    }
}

void display(Process proc[], int n){
    cout<<"Shortest Job First"<<endl;
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
    for (int i=0; i<n; i++){
        cout<<proc[i].PID<<"\t"<<proc[i].AT<<"\t"<<proc[i].BT<<"\t"<<proc[i].CT<<"\t"<<proc[i].WT<<"\t"<<proc[i].TAT<<"\t"<<endl;
    }
}


int main(){
    Process proc[5] = {{1,0,5}, {2, 2, 3}, {3, 1, 8},{4,4,2},{5,3,4}};
    SJB(proc, 5);
    display(proc, 5);
    return 0;

}