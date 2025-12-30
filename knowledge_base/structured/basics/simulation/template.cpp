#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Example: Climbing Worm simulation
    int n, u, d;
    cin >> u >> d >> n;
    int time = 0, dist = 0;
    while (true) {
        dist += u;
        time++;
        if (dist >= n) break;
        dist -= d;
    }
    cout << time << '\n';
    return 0;
}