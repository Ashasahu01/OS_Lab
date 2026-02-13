#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Process {
    int pid,at,bt,rt,ct,tat,wt,rem_bt;
};


void sortByArrival(struct Process *p, int n) {
    struct Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process *p, int n) {
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void fcfs(struct Process *p, int n) {
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(time < p[i].at) 
            time = p[i].at;
        
        p[i].rt=time - p[i].at;
        p[i].ct = time + p[i].bt;
        time = p[i].ct;
    }
    calculateTimes(p, n);
}



void printTable(struct Process *p, int n) {
    int i;
    float total_tat = 0, total_wt = 0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("--------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt,
                p[i].rt);

        total_tat += p[i].tat;
        total_wt  += p[i].wt;
    }

    printf("\n");
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time    = %.2f\n", total_wt / n);
}


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    
    sortByArrival(p, n);
    fcfs(p, n);
    printTable(p, n);

    return 0;
}