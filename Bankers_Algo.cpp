// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
int main() {
    // Write C++ code here
    int n = 5;
    int r= 3;
    int alloc[5][3] = {{0, 0, 1},
                       {3, 0, 0},
                       {1, 0, 1},
                       {2, 3, 2},
                       {0, 0, 3}};
    int max[5][3] = {{7, 6, 3},
                       {3, 2, 2},
                       {8, 0, 2},
                       {2, 1, 2},
                       {5, 2, 3}};
    
    int avail[3] = {2, 3, 2};
    int need[5][3];
    int f[n], ans[n];
    int ind = 0;
    
    for(int i=0; i<n; i++){
        for (int j=0; j<r;j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    for(int k=0; k<n; k++){
        f[k] = 0;
    }
    
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            if (f[i] == 0){
                int flag = 0;
                for(int j=0; j<r; j++){
                    if (need[i][j]>avail[j]){
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0){
                    f[i] = 1;
                    ans[ind++] = i;
                    for (int j=0; j<r;j++){
                        avail[j] += alloc[i][j];
                    }
                }
            }
        }
    }
    
    
    for(int i=0; i<5;i++){
        cout<<ans[i]<<"->";
    }
    cout<<'\r';
    
    
    
    
    return 0;
}