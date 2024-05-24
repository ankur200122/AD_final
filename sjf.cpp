#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int completionTime; // Completion Time
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
    int responseTime; // Response Time
};

bool compareArrival(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void calculateTimes(vector<Process>& proc, int n) {
    vector<bool> isCompleted(n, false);
    int currentTime = 0;
    int completed = 0;

    while (completed != n) {
        int idx = -1;
        int shortestBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].burstTime < shortestBurst) {
                shortestBurst = proc[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            if (proc[idx].completionTime == 0) {
                proc[idx].responseTime = currentTime - proc[idx].arrivalTime;
            }

            currentTime += proc[idx].burstTime;
            proc[idx].completionTime = currentTime;
            proc[idx].turnAroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnAroundTime - proc[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        } else {
            currentTime++;
        }
    }
}

void calculateAverageTimes(vector<Process>& proc, int n) {
    calculateTimes(proc, n);

    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalCompletionTime = 0, totalResponseTime = 0;

    cout << "Processes  Arrival Time  Burst Time  Completion Time  Waiting Time  Turnaround Time  Response Time\n";

    // Sort processes by process ID for sequential output
    sort(proc.begin(), proc.end(), [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });

    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnAroundTime;
        totalCompletionTime += proc[i].completionTime;
        totalResponseTime += proc[i].responseTime;

        cout << "   " << proc[i].pid << "\t\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].completionTime << "\t\t"
             << proc[i].waitingTime << "\t\t" << proc[i].turnAroundTime << "\t\t"
             << proc[i].responseTime << endl;
    }

    cout << "Average waiting time = " << (float)totalWaitingTime / n << endl;
    cout << "Average turn around time = " << (float)totalTurnAroundTime / n << endl;
    cout << "Average completion time = " << (float)totalCompletionTime / n << endl;
    cout << "Average response time = " << (float)totalResponseTime / n << endl;
}

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> proc(n);

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        cout << "Enter arrival time for process " << proc[i].pid << ": ";
        cin >> proc[i].arrivalTime;
        cout << "Enter burst time for process " << proc[i].pid << ": ";
        cin >> proc[i].burstTime;
    }

    // Sort processes by arrival time
    sort(proc.begin(), proc.end(), compareArrival);

    calculateAverageTimes(proc, n);

    return 0;
}
