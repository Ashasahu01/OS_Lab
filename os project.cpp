#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt, rt, remaining_bt;
};

// Utility function to print result table
void printTable(vector<Process> &p) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &pr : p)
        cout << pr.id << "\t" << pr.at << "\t" << pr.bt << "\t" 
             << pr.ct << "\t" << pr.tat << "\t" << pr.wt << "\n";
    
    float avg_tat = 0, avg_wt = 0;
    for (auto &pr : p) {
        avg_tat += pr.tat;
        avg_wt += pr.wt;
    }
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avg_tat / p.size();
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avg_wt / p.size() << "\n";
}

// ====================== FCFS ======================
void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });

    int current_time = 0;
    for (auto &pr : p) {
        if (current_time < pr.at)
            current_time = pr.at;
        pr.ct = current_time + pr.bt;
        current_time = pr.ct;

        pr.tat = pr.ct - pr.at;
        pr.wt = pr.tat - pr.bt;
    }

    cout << "\n--- FCFS Scheduling ---";
    printTable(p);
}

// ====================== SJF (Non-Preemptive) ======================
void sjf(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.bt < b.bt;
        return a.at < b.at;
    });

    int completed = 0, current_time = 0;
    vector<bool> done(p.size(), false);
    while (completed < p.size()) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < p.size(); i++) {
            if (!done[i] && p[i].at <= current_time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { current_time++; continue; }

        current_time += p[idx].bt;
        p[idx].ct = current_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }

    cout << "\n--- SJF (Non-Preemptive) Scheduling ---";
    printTable(p);
}

// ====================== SRTF (Preemptive) ======================
void srtf(vector<Process> p) {
    for (auto &pr : p) pr.remaining_bt = pr.bt;
    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });

    int complete = 0, t = 0, n = p.size();
    while (complete != n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].remaining_bt > 0 && p[i].remaining_bt < min_bt) {
                min_bt = p[i].remaining_bt;
                idx = i;
            }
        }
        if (idx == -1) { t++; continue; }

        p[idx].remaining_bt--;
        t++;

        if (p[idx].remaining_bt == 0) {
            complete++;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    cout << "\n--- SRTF (Preemptive) Scheduling ---";
    printTable(p);
}

// ====================== Round Robin ======================
void rr(vector<Process> p, int tq) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });

    queue<int> q;
    vector<bool> inQueue(p.size(), false);
    for (auto &pr : p) pr.remaining_bt = pr.bt;

    int current_time = 0, completed = 0, n = p.size();
    q.push(0);
    inQueue[0] = true;

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        if (p[idx].remaining_bt > tq) {
            current_time = max(current_time, p[idx].at) + tq;
            p[idx].remaining_bt -= tq;
        } else {
            current_time = max(current_time, p[idx].at) + p[idx].remaining_bt;
            p[idx].remaining_bt = 0;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_bt > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        // If current process still has burst time left, re-add it
        if (p[idx].remaining_bt > 0)
            q.push(idx);
    }

    cout << "\n--- Round Robin Scheduling (TQ = " << tq << ") ---";
    printTable(p);
}

// ====================== HRRN ======================
void hrrn(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });

    int completed = 0, current_time = 0, n = p.size();
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1;
        double max_rr = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= current_time) {
                double rr = (double)(p[i].bt + (current_time - p[i].at)) / p[i].bt;
                if (rr > max_rr) {
                    max_rr = rr;
                    idx = i;
                }
            }
        }

        if (idx == -1) { current_time++; continue; }

        current_time += p[idx].bt;
        p[idx].ct = current_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }

    cout << "\n--- HRRN Scheduling ---";
    printTable(p);
}

// ====================== MAIN ======================
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;
    }

    int choice;
    cout << "\nSelect CPU Scheduling Algorithm:\n";
    cout << "1. FCFS\n2. SJF (Non-Preemptive)\n3. SRTF (Preemptive)\n4. Round Robin\n5. HRRN\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: fcfs(p); break;
        case 2: sjf(p); break;
        case 3: srtf(p); break;
        case 4: {
            int tq;
            cout << "Enter Time Quantum: ";
            cin >> tq;
            rr(p, tq);
            break;
        }
        case 5: hrrn(p); break;
        default: cout << "Invalid Choice!"; break;
    }

    return 0;
}
