#include <stdio.h>

#define NUM_PARTITIONS 6
#define NUM_PROCESSES 5

void print_partitions(int partitions[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d KB\t", partitions[i]);
    }
    printf("\n");
}

void first_fit(int partitions[], int processes[]) {
    int temp_partitions[NUM_PARTITIONS];
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        temp_partitions[i] = partitions[i];
    }

    printf("First-fit:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d KB -> ", processes[i]);
        int j;
        for (j = 0; j < NUM_PARTITIONS; j++) {
            if (temp_partitions[j] >= processes[i]) {
                temp_partitions[j] -= processes[i];
                printf("Partition %d KB\n", partitions[j]);
                break;
            }
        }
        if (j == NUM_PARTITIONS) {
            printf("Not enough memory\n");
        }
    }
    print_partitions(temp_partitions, NUM_PARTITIONS);
}

void best_fit(int partitions[], int processes[]) {
    int temp_partitions[NUM_PARTITIONS];
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        temp_partitions[i] = partitions[i];
    }

    printf("Best-fit:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d KB -> ", processes[i]);
        int min_idx = -1, min_diff = 10000;
        for (int j = 0; j < NUM_PARTITIONS; j++) {
            if (temp_partitions[j] >= processes[i] && (temp_partitions[j] - processes[i] < min_diff)) {
                min_diff = temp_partitions[j] - processes[i];
                min_idx = j;
            }
        }
        if (min_idx != -1) {
            temp_partitions[min_idx] -= processes[i];
            printf("Partition %d KB\n", partitions[min_idx]);
        } else {
            printf("Not enough memory\n");
        }
    }
    print_partitions(temp_partitions, NUM_PARTITIONS);
}

void worst_fit(int partitions[], int processes[]) {
    int temp_partitions[NUM_PARTITIONS];
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        temp_partitions[i] = partitions[i];
    }

    printf("Worst-fit:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d KB -> ", processes[i]);
        int max_idx = -1, max_size = -1;
        for (int j = 0; j < NUM_PARTITIONS; j++) {
            if (temp_partitions[j] >= processes[i] && temp_partitions[j] > max_size) {
                max_size = temp_partitions[j];
                max_idx = j;
            }
        }
        if (max_idx != -1) {
            temp_partitions[max_idx] -= processes[i];
            printf("Partition %d KB\n", partitions[max_idx]);
        } else {
            printf("Not enough memory\n");
        }
    }
    print_partitions(temp_partitions, NUM_PARTITIONS);
}

int main() {
    int partitions[NUM_PARTITIONS] = {300, 600, 350, 200, 750, 125};
    int processes[NUM_PROCESSES] = {115, 500, 358, 200, 375};

    printf("Initial memory partitions:\n");
    print_partitions(partitions, NUM_PARTITIONS);
    printf("\n");

    first_fit(partitions, processes);
    printf("\n");
    best_fit(partitions, processes);
    printf("\n");
    worst_fit(partitions, processes);

    return 0;
}
