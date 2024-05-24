#include <iostream>
#include <vector>
#include <algorithm>

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

// Function to sort processes by arrival time
bool compareArrival(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

// Function to calculate waiting time, turnaround time, response time, and completion time
void calculateTimes(vector<Process>& proc, int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }

        proc[i].responseTime = currentTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].responseTime;
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;

        currentTime += proc[i].burstTime;
    }
}

// Function to calculate average times and print results
void calculateAverageTimes(vector<Process>& proc, int n) {
    calculateTimes(proc, n);

    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalCompletionTime = 0, totalResponseTime = 0;

    cout << "Processes  Arrival Time  Burst Time  Completion Time  Waiting Time  Turnaround Time  Response Time\n";

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
