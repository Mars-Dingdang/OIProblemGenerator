#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Convert decimal n to balanced ternary digits (1, 0, -1)
// Returns vector of digits from least significant to most significant
vector<int> toBalancedTernary(long long n) {
    vector<int> digits;
    while (n != 0) {
        int rem = n % 3;
        n /= 3;
        if (rem == 2) {
            rem = -1; // Represent -1 as 'Z'
            n += 1;
        } else if (rem == 3) { // This case handles carry from previous step
            rem = 0;
            n += 1;
        }
        digits.push_back(rem);
    }
    return digits;
}

// Convert balanced ternary digits (1, 0, -1) back to decimal
long long fromBalancedTernary(const vector<int>& digits) {
    long long result = 0;
    long long power = 1;
    for (int d : digits) {
        result += d * power;
        power *= 3;
    }
    return result;
}

// Print balanced ternary digits (using 'Z' for -1)
void printBalancedTernary(const vector<int>& digits) {
    if (digits.empty()) {
        cout << "0";
        return;
    }
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] == -1) cout << 'Z';
        else cout << digits[i];
    }
}

int main() {
    long long n;
    cout << "Enter a decimal number: ";
    cin >> n;
    
    vector<int> bt = toBalancedTernary(n);
    cout << "Balanced ternary: ";
    printBalancedTernary(bt);
    cout << endl;
    
    long long back = fromBalancedTernary(bt);
    cout << "Converted back: " << back << endl;
    
    return 0;
}