#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int remainingTime; // Remaining Time
    int completionTime; // Completion Time
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
    int responseTime; // Response Time
    bool isStarted; // To check if process has started
};

// Function to sort processes by arrival time
bool compareArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

// Function to perform round robin scheduling
void calculateTimes(vector<Process>& proc, int n, int quantum) {
    queue<int> q;
    int currentTime = 0;
    int completed = 0;
    int prevTime = 0;

    // Sort processes by arrival time
    sort(proc.begin(), proc.end(), compareArrivalTime);

    q.push(0);
    proc[0].isStarted = true;

    while (completed != n) {
        int idx = q.front();
        q.pop();

        if (proc[idx].remainingTime == proc[idx].burstTime) {
            proc[idx].responseTime = currentTime - proc[idx].arrivalTime;
        }

        if (proc[idx].remainingTime > quantum) {
            currentTime += quantum;
            proc[idx].remainingTime -= quantum;
        } else {
            currentTime += proc[idx].remainingTime;
            proc[idx].remainingTime = 0;
            proc[idx].completionTime = currentTime;
            proc[idx].turnAroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnAroundTime - proc[idx].burstTime;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].isStarted && proc[i].remainingTime > 0) {
                q.push(i);
                proc[i].isStarted = true;
            }
        }

        if (proc[idx].remainingTime > 0) {
            q.push(idx);
        }

        if (q.empty()) {
            for (int i = 0; i < n; i++) {
                if (proc[i].remainingTime > 0) {
                    q.push(i);
                    proc[i].isStarted = true;
                    break;
                }
            }
        }
    }
}

// Function to calculate average times and print results
void calculateAverageTimes(vector<Process>& proc, int n, int quantum) {
    calculateTimes(proc, n, quantum);

    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    cout << "Processes  Arrival time  Burst time  Completion time  Waiting time  Turn around time  Response time\n";

    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnAroundTime;
        totalResponseTime += proc[i].responseTime;
        cout << "   " << proc[i].pid << "\t\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].completionTime << "\t\t"
             << proc[i].waitingTime << "\t\t" << proc[i].turnAroundTime << "\t\t"
             << proc[i].responseTime << endl;
    }

    cout << "Average waiting time = " << (float)totalWaitingTime / n << endl;
    cout << "Average turn around time = " << (float)totalTurnAroundTime / n << endl;
    cout << "Average response time = " << (float)totalResponseTime / n << endl;
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> proc(n);

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        cout << "Enter arrival time for process " << proc[i].pid << ": ";
        cin >> proc[i].arrivalTime;
        cout << "Enter burst time for process " << proc[i].pid << ": ";
        cin >> proc[i].burstTime;
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].isStarted = false;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    calculateAverageTimes(proc, n, quantum);

    return 0;
}
