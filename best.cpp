#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Partition {
    int size;
    bool isOccupied;
};

struct Process {
    int size;
    int partitionIndex; // -1 if not allocated
};

void bestFit(vector<Partition>& partitions, vector<Process>& processes) {
    for (auto& process : processes) {
        int bestIndex = -1;
        int minSize = INT_MAX;
        process.partitionIndex = -1;
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

void resetPartitions(vector<Partition>& partitions) {
    for (auto& partition : partitions) {
        partition.isOccupied = false;
    }
}

void printResults(const vector<Process>& processes) {
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

    // Apply Best Fit
    bestFit(partitions, processes);
    printResults(processes);

    return 0;
}
