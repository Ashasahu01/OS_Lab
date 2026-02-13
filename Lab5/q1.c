#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid,at,bt,rt,ct,tat,wt,rem_bt;
};

void ganttChart(struct Process *p, int n) {
    int i;

    printf("\nGantt Chart:\n|");

    for(i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }

    printf("\n");

    for(i = 0; i < n; i++) {
        printf("    %d", p[i].ct);
    }

    printf("\n");
}

void printTable(){

}

int main(){
    ganttChart();
}