#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int remainingTime; // Remaining Time
    int priority; // Priority (lower value means higher priority)
    int completionTime; // Completion Time
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
    int responseTime; // Response Time
    bool isStarted; // To check if the process has started
};

bool compareArrival(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void calculateTimes(vector<Process>& proc, int n) {
    int currentTime = 0;
    int completed = 0;
    int lastExecuted = -1;
    
    while (completed != n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
                if (proc[i].priority < highestPriority ||
                    (proc[i].priority == highestPriority && proc[i].arrivalTime < proc[idx].arrivalTime)) {
                    highestPriority = proc[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (!proc[idx].isStarted) {
                proc[idx].responseTime = currentTime - proc[idx].arrivalTime;
                proc[idx].isStarted = true;
            }

            proc[idx].remainingTime--;
            currentTime++;
            lastExecuted = idx;

            if (proc[idx].remainingTime == 0) {
                proc[idx].completionTime = currentTime;
                proc[idx].turnAroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                proc[idx].waitingTime = proc[idx].turnAroundTime - proc[idx].burstTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}

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
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].isStarted = false;
    }

    // Sort processes by arrival time
    sort(proc.begin(), proc.end(), compareArrival);

    calculateAverageTimes(proc, n);

    return 0;
}
