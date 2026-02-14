#include<stdio.h>
#include<limits.h>
#define MAX 100

typedef struct
{
    int pid, at, bt;
    int ct, tat, wt, rt;
    int remaining;
    int started;
    int done;
} Process;

Process p[MAX];
int n;

void input()
{
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Arrival Time P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Burst Time P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        p[i].remaining = p[i].bt;
        p[i].started = 0;
        p[i].done = 0;
    }
}

void reset()
{
    for (int i = 0; i < n; i++)
    {
        p[i].remaining = p[i].bt;
        p[i].started = 0;
        p[i].done = 0;
    }
}

void metrics()
{
    double avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("\nPID AT BT CT TAT WT RT\n");

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        avg_rt += p[i].rt;

        printf("P%d  %d  %d  %d  %d  %d  %d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat,
               p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT  = %.2f", avg_wt / n);
    printf("\nAverage RT  = %.2f\n", avg_rt / n);
}

void print_line(int count)
{
    for (int i = 0; i < count; i++)
        printf("--------");
    printf("-\n");
}

void fcfs()
{
    reset();
    int time = 0;

    printf("\nGantt Chart:\n");
    print_line(n);

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
            time = p[i].at;

        p[i].rt = time - p[i].at;
        time += p[i].bt;
        p[i].ct = time;

        printf("|  P%d   ", p[i].pid);
    }
    printf("|\n");

    print_line(n);

    printf("0");
    time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
            time = p[i].at;
        time += p[i].bt;
        printf("      %d", time);
    }
    printf("\n");

    metrics();
}

void sjf()
{
    reset();
    int time = 0, completed = 0;
    int order[MAX], k = 0;

    while (completed < n)
    {
        int idx = -1, min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!p[i].done && p[i].at <= time &&
                p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        p[idx].rt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].done = 1;

        order[k++] = idx;
        completed++;
    }

    printf("\nGantt Chart:\n");
    print_line(k);

    for (int i = 0; i < k; i++)
        printf("|  P%d   ", p[order[i]].pid);
    printf("|\n");

    print_line(k);

    printf("0");
    for (int i = 0; i < k; i++)
        printf("      %d", p[order[i]].ct);
    printf("\n");

    metrics();
}

void srtf()
{
    reset();
    int time = 0, completed = 0;
    int last = -1;
    int order[1000], k = 0;

    while (completed < n)
    {
        int idx = -1, min_rem = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time &&
                p[i].remaining > 0 &&
                p[i].remaining < min_rem)
            {
                min_rem = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        if (!p[idx].started)
        {
            p[idx].rt = time - p[idx].at;
            p[idx].started = 1;
        }

        if (last != idx)
        {
            order[k++] = idx;
            last = idx;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0)
        {
            p[idx].ct = time;
            completed++;
        }
    }

    printf("\nGantt Chart:\n");
    print_line(k);

    for (int i = 0; i < k; i++)
        printf("|  P%d   ", p[order[i]].pid);
    printf("|\n");

    print_line(k);

    printf("0");
    for (int i = 0; i < k; i++)
        printf("      ");
    printf("\n");

    metrics();
}

int main()
{
    int choice;

    printf("Number of processes: ");
    scanf("%d", &n);

    input();

    printf("\n1.FCFS\n2.SJF\n3.SRTF\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1)
        fcfs();
    else if (choice == 2)
        sjf();
    else if (choice == 3)
        srtf();
    else
        printf("Invalid choice");

    return 0;
}