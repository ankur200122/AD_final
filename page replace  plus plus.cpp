#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class OptimalPageReplacement {
public:
    OptimalPageReplacement(int frames) : frameCount(frames) {}

    void processPageReference(const vector<int>& pageReferences) {
        int n = pageReferences.size();

        for (int i = 0; i < n; i++) {
            int page = pageReferences[i];

            if (isHit(page)) {
                cout << "Page " << page << ": Hit\n";
                hitCount++;
            } else {
                cout << "Page " << page << ": Miss\n";
                if (frames.size() < frameCount) {
                    frames.insert(page);
                } else {
                    int pageToRemove = findOptimalPageToRemove(pageReferences, i);
                    frames.erase(pageToRemove);
                    frames.insert(page);
                }
                missCount++;
            }
        }
    }

    void printHitMissRatio() {
        cout << "Hits: " << hitCount << "\n";
        cout << "Misses: " << missCount << "\n";
        cout << "Hit Ratio: " << static_cast<float>(hitCount) / (hitCount + missCount) << "\n";
        cout << "Miss Ratio: " << static_cast<float>(missCount) / (hitCount + missCount) << "\n";
    }

private:
    int frameCount;
    unordered_set<int> frames;
    int hitCount = 0;
    int missCount = 0;

    bool isHit(int page) {
        return frames.find(page) != frames.end();
    }

    int findOptimalPageToRemove(const vector<int>& pageReferences, int currentIndex) {
        unordered_map<int, int> futureUse;
        for (int i = currentIndex + 1; i < pageReferences.size(); i++) {
            if (frames.find(pageReferences[i]) != frames.end() && futureUse.find(pageReferences[i]) == futureUse.end()) {
                futureUse[pageReferences[i]] = i;
            }
        }

        int pageToRemove = -1;
        int farthestUse = currentIndex;

        for (auto frame : frames) {
            if (futureUse.find(frame) == futureUse.end()) {
                return frame; // This page is not used again, so remove it
            }
            if (futureUse[frame] > farthestUse) {
                farthestUse = futureUse[frame];
                pageToRemove = frame;
            }
        }

        return pageToRemove;
    }
};

int main() {
    int frameCount, pageCount;

    cout << "Enter number of frames: ";
    cin >> frameCount;
    cout << "Enter number of pages: ";
    cin >> pageCount;

    vector<int> pageReferences(pageCount);
    cout << "Enter the page reference string: ";
    for (int i = 0; i < pageCount; i++) {
        cin >> pageReferences[i];
    }

    OptimalPageReplacement optimal(frameCount);
    optimal.processPageReference(pageReferences);
    optimal.printHitMissRatio();

    return 0;
}
