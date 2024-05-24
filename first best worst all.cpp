#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Partition {
    int size;
    bool isOccupied;
};

struct Process {
    int size;
    int partitionIndex; // -1 if not allocated
};

void firstFit(vector<Partition>& partitions, vector<Process>& processes) {
    for (auto& process : processes) {
        process.partitionIndex = -1;
        for (int j = 0; j < partitions.size(); j++) {
            if (!partitions[j].isOccupied && partitions[j].size >= process.size) {
                partitions[j].isOccupied = true;
                process.partitionIndex = j;
                break;
            }
        }
    }
}

void bestFit(vector<Partition>& partitions, vector<Process>& processes) {
    for (auto& process : processes) {
        process.partitionIndex = -1;
        int bestIndex = -1;
        int minSize = INT_MAX;
        for (int j = 0; j < partitions.size(); j++) {
            if (!partitions[j].isOccupied && partitions[j].size >= process.size && partitions[j].size < minSize) {
                minSize = partitions[j].size;
                bestIndex = j;
            }
        }
        if (bestIndex != -1) {
            partitions[bestIndex].isOccupied = true;
            process.partitionIndex = bestIndex;
        }
    }
}

void worstFit(vector<Partition>& partitions, vector<Process>& processes) {
    for (auto& process : processes) {
        process.partitionIndex = -1;
        int worstIndex = -1;
        int maxSize = 0;
        for (int j = 0; j < partitions.size(); j++) {
            if (!partitions[j].isOccupied && partitions[j].size >= process.size && partitions[j].size > maxSize) {
                maxSize = partitions[j].size;
                worstIndex = j;
            }
        }
        if (worstIndex != -1) {
            partitions[worstIndex].isOccupied = true;
            process.partitionIndex = worstIndex;
        }
    }
}

void resetPartitions(vector<Partition>& partitions) {
    for (auto& partition : partitions) {
        partition.isOccupied = false;
    }
}

int calculateRemainingSpace(const vector<Partition>& partitions) {
    int remainingSpace = 0;
    for (const auto& partition : partitions) {
        if (!partition.isOccupied) {
            remainingSpace += partition.size;
        }
    }
    return remainingSpace;
}

void printResults(const vector<Process>& processes, const string& method) {
    cout << method << " Results:\n";
    cout << "Process Size | Partition Index\n";
    for (const auto& process : processes) {
        cout << process.size << " | " << (process.partitionIndex == -1 ? "Not Allocated" : to_string(process.partitionIndex)) << endl;
    }
}

int main() {
    int numPartitions, numProcesses;

    cout << "Enter number of partitions: ";
    cin >> numPartitions;
    vector<Partition> partitions(numPartitions);
    for (int i = 0; i < numPartitions; i++) {
        cout << "Enter size of partition " << i + 1 << ": ";
        cin >> partitions[i].size;
        partitions[i].isOccupied = false;
    }

    cout << "Enter number of processes: ";
    cin >> numProcesses;
    vector<Process> processes(numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter size of process " << i + 1 << ": ";
        cin >> processes[i].size;
    }

    // First Fit
    resetPartitions(partitions);
    firstFit(partitions, processes);
    printResults(processes, "First Fit");
    int remainingFirstFit = calculateRemainingSpace(partitions);

    // Best Fit
    resetPartitions(partitions);
    bestFit(partitions, processes);
    printResults(processes, "Best Fit");
    int remainingBestFit = calculateRemainingSpace(partitions);

    // Worst Fit
    resetPartitions(partitions);
    worstFit(partitions, processes);
    printResults(processes, "Worst Fit");
    int remainingWorstFit = calculateRemainingSpace(partitions);

    cout << "\nRemaining space after allocation:\n";
    cout << "First Fit: " << remainingFirstFit << endl;
    cout << "Best Fit: " << remainingBestFit << endl;
    cout << "Worst Fit: " << remainingWorstFit << endl;

    string bestMethod = "First Fit";
    int minRemaining = remainingFirstFit;

    if (remainingBestFit < minRemaining) {
        bestMethod = "Best Fit";
        minRemaining = remainingBestFit;
    }
    if (remainingWorstFit < minRemaining) {
        bestMethod = "Worst Fit";
        minRemaining = remainingWorstFit;
    }

    cout << "\nBest method is " << bestMethod << " with " << minRemaining << " remaining space." << endl;

    return 0;
}
