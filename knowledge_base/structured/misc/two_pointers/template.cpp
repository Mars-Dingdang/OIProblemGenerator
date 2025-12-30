#include <vector>
#include <utility>
using namespace std;

pair<bool, vector<int>> detect_cycle(vector<int>& nxt) {
    // nxt[i] points to next node (0-indexed), -1 means no next node
    int fast = 0, slow = 0;
    // First, detect if there's a cycle
    do {
        if (nxt[fast] == -1 || nxt[nxt[fast]] == -1) {
            return {false, {}}; // No cycle
        }
        fast = nxt[nxt[fast]];
        slow = nxt[slow];
    } while (fast != slow);
    // Find the entry point of the cycle
    slow = 0;
    while (slow != fast) {
        slow = nxt[slow];
        fast = nxt[fast];
    }
    // Extract the entire cycle
    vector<int> cycle;
    do {
        cycle.push_back(slow);
        slow = nxt[slow];
    } while (slow != fast);
    return {true, cycle};
}