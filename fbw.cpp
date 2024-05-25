#include <iostream>

using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "First Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "Best Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "Worst Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main() {
    int m, n, choice;

    cout << "Enter number of blocks: ";
    cin >> m;
    int blockSize[m];
    int originalBlockSize[m];
    cout << "Enter block sizes:\n";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
        originalBlockSize[i] = blockSize[i];
    }

    cout << "Enter number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> processSize[i];

    do {
        cout << "\nMemory Allocation Menu:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Reset block sizes to their original values before each allocation
        for (int i = 0; i < m; i++) {
            blockSize[i] = originalBlockSize[i];
        }

        switch (choice) {
            case 1:
                firstFit(blockSize, m, processSize, n);
                break;
            case 2:
                bestFit(blockSize, m, processSize, n);
                break;
            case 3:
                worstFit(blockSize, m, processSize, n);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
