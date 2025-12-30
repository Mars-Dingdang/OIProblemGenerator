#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Example: Sequential zero-sum game (minimax) for a simple array game
int minimax(const vector<int>& arr, int left, int right, bool isMaxPlayer) {
    if (left == right) return arr[left];
    
    if (isMaxPlayer) {
        return max(minimax(arr, left + 1, right, false),
                   minimax(arr, left, right - 1, false));
    } else {
        return min(minimax(arr, left + 1, right, true),
                   minimax(arr, left, right - 1, true));
    }
}

// Example: Solving a simultaneous zero-sum game via linear programming (simplified)
// Note: This is a placeholder; real implementation requires LP solver.
void solveSimultaneousGame(const vector<vector<double>>& payoffMatrix) {
    // This function would typically use linear programming to find optimal mixed strategies.
    // For simplicity, we just print the matrix.
    cout << "Payoff matrix (player 1):" << endl;
    for (const auto& row : payoffMatrix) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }
    // In practice, solve LP: max u s.t. sum_i s1[i]*payoff[i][j] >= u for all j, sum s1 = 1, s1 >= 0
}

int main() {
    // Example usage for sequential game
    vector<int> arr = {3, 5, 2, 7};
    int result = minimax(arr, 0, arr.size() - 1, true);
    cout << "Optimal result for sequential game: " << result << endl;
    
    // Example for simultaneous game
    vector<vector<double>> payoff = {{0, -1, 1},
                                     {1, 0, -1},
                                     {-1, 1, 0}};
    solveSimultaneousGame(payoff);
    return 0;
}