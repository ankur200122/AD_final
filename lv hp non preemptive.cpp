#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int priority; // Priority (lower value means higher priority)
    int completionTime; // Completion Time
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
    int responseTime; // Response Time
};

// Function to sort processes by arrival time and priority
bool compareArrivalPriority(const Process& a, const Process& b) {
    if (a.arrivalTime == b.arrivalTime) {
        return a.priority < b.priority; // Lower priority value first
    }
    return a.arrivalTime < b.arrivalTime;
}

// Function to calculate waiting time, turnaround time, and completion time
void calculateTimes(vector<Process>& proc, int n) {
    vector<int> isCompleted(n, 0);
    int currentTime = 0, completed = 0;
    vector<bool> firstResponse(n, false);

    while (completed != n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (proc[i].priority < highestPriority) {
                    highestPriority = proc[i].priority;
                    idx = i;
                }
                if (proc[i].priority == highestPriority) {
                    if (proc[i].arrivalTime < proc[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (!firstResponse[idx]) {
                proc[idx].responseTime = currentTime - proc[idx].arrivalTime;
                firstResponse[idx] = true;
            }

            proc[idx].completionTime = currentTime + proc[idx].burstTime;
            proc[idx].turnAroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnAroundTime - proc[idx].burstTime;

            currentTime = proc[idx].completionTime;
            isCompleted[idx] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }
}

// Function to calculate average times and print results
void calculateAverageTimes(vector<Process>& proc, int n) {
    calculateTimes(proc, n);

    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalCompletionTime = 0, totalResponseTime = 0;

    cout << "Processes  Arrival Time  Burst Time  Priority  Completion Time  Waiting Time  Turnaround Time  Response Time\n";

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
             << proc[i].burstTime << "\t\t" << proc[i].priority << "\t\t"
             << proc[i].completionTime << "\t\t" << proc[i].waitingTime << "\t\t"
             << proc[i].turnAroundTime << "\t\t" << proc[i].responseTime << endl;
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
        cout << "Enter priority for process " << proc[i].pid << " (lower value means higher priority): ";
        cin >> proc[i].priority;
    }

    // Sort processes by arrival time and priority
    sort(proc.begin(), proc.end(), compareArrivalPriority);

    calculateAverageTimes(proc, n);

    return 0;
}
