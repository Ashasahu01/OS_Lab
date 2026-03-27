#include <stdio.h>
#include <stdlib.h>

//Each process block has this block structure
struct block {
    int start;   // starting address
    int size;  //memory size we required for each process
    int free;
    int pid;
};

struct block memory[MAX];
int n;

void firstFit(int pid, int size);
void bestFit(int pid, int size);
void worstFit(int pid, int size);
void releaseProcess(int pid);
void report();

int main() {
    int choice = 0, pid, size, algo;

    int addr = 0;

    printf("Enter size of each %d block: ", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &memory[i].size);

        memory[i].start = addr;
        addr += memory[i].size;

        memory[i].free = 1;
        memory[i].pid = -1;
}

    while(choice != 4) {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Request (Process Allocation)\n");
        printf("2. Release\n");
        printf("3. Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1: // Request
                printf("Enter Process ID and required Memory space: ");
                scanf("%d %d", &pid, &size);

                printf("\nChoose Allocation Algorithm:\n");
                printf("1. First Fit\n");
                printf("2. Best Fit\n");
                printf("3. Worst Fit\n");
                printf("Enter choice: ");
                scanf("%d", &algo);

                if(algo == 1)
                    firstFit(pid, size);
                else if(algo == 2)
                    bestFit(pid, size);
                else if(algo == 3)
                    worstFit(pid, size);
                else
                    printf("Invalid Algorithm!\n");
                break;

            case 2: // Release
                printf("Enter Process ID to Release: ");
                scanf("%d", &pid);
                releaseProcess(pid);
                break;

            case 3: // Report
                report();
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

//First Fit Algorithm 
void firstFit(int pid, int size){//allote first block that is big enough for the process
    for(int i = 0; i<n; i++){//scan 0 - n
        if (memory[i].free && memory[i].size >= size) {
            memory[i].free = 0;
            memory[i].pid = pid;
            printf("Process %d allocated to block %d using First Fit\n", pid, i);
            return;
        }
    }
    printf("Memory not allocated for Process %d (First Fit)\n", pid);
}

//Best Fit Algorithm
void bestFit(int pid, int size){ //Allocate the smallest block that is big enough for the process 
    int bestIndex = -1;

    for (int i = 0; i < n; i++) {
        if (memory[i].free && memory[i].size >= size) {
            if (bestIndex == -1 || memory[i].size < memory[bestIndex].size) {
                bestIndex = i;
            }
        }
    }

     if (bestIndex != -1) {
        memory[bestIndex].free = 0;
        memory[bestIndex].pid = pid;
        printf("Process %d allocated to block %d using Best Fit\n", pid, bestIndex);
    } else {
        printf("Memory not allocated for Process %d (Best Fit)\n", pid);
    }
}

// Worst Fit Algorithm
void worstFit(int pid, int size) { //Allocate the largest available block
    int worstIndex = -1;

    for (int i = 0; i < n; i++) {
        if (memory[i].free && memory[i].size >= size) {
            if (worstIndex == -1 || memory[i].size > memory[worstIndex].size) {
                worstIndex = i;
            }
        }
    }

    if (worstIndex != -1) {
        memory[worstIndex].free = 0;
        memory[worstIndex].pid = pid;
        printf("Process %d allocated to block %d using Worst Fit\n", pid, worstIndex);
    } else {
        printf("Memory not allocated for Process %d (Worst Fit)\n", pid);
    }
}

//Function to release process
void releaseProcess(int pid) {
    for (int i = 0; i < n; i++) {
        if (!memory[i].free && memory[i].pid == pid) {
            memory[i].free = 1;
            memory[i].pid = -1;
            printf("Process %d released from block %d\n", pid, i);
            return;
        }
    }
    printf("Process %d not found!\n", pid);
}

//Display Report
void report() {
    printf("\nMemory Report:\n");
    printf("Block\tSize\tStatus\t\tPID\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%s\t", i, memory[i].size,
               memory[i].free ? "Free" : "Allocated");

        if (memory[i].free)
            printf("-\n");
        else
            printf("%d\n", memory[i].pid);
    }
}