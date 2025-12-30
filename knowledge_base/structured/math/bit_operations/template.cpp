#include <bits/stdc++.h>
using namespace std;

// Basic operations
template<typename T>
T getBit(T x, int pos) { return (x >> pos) & 1; }

template<typename T>
T setBit(T x, int pos) { return x | (1LL << pos); }

template<typename T>
T clearBit(T x, int pos) { return x & ~(1LL << pos); }

template<typename T>
T toggleBit(T x, int pos) { return x ^ (1LL << pos); }

// Lowbit: get lowest set bit
int lowbit(int x) { return x & -x; }

// Count set bits (popcount)
int popcount(int x) {
    int cnt = 0;
    while (x) {
        cnt++;
        x -= lowbit(x);
    }
    return cnt;
}

// Check if x is power of two
bool isPowerOfTwo(int x) { return x > 0 && (x & (x - 1)) == 0; }

// Swap two integers (without extra variable)
void swapInts(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

// Absolute value (without branching)
int absInt(int x) {
    int mask = x >> (sizeof(int) * 8 - 1);
    return (x + mask) ^ mask;
}

int main() {
    // Example usage
    int a = 5, b = 3;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "a ^ b = " << (a ^ b) << endl;
    cout << "~a = " << (~a) << endl;
    cout << "a << 1 = " << (a << 1) << endl;
    cout << "a >> 1 = " << (a >> 1) << endl;
    cout << "popcount(a) = " << popcount(a) << endl;
    cout << "isPowerOfTwo(8) = " << isPowerOfTwo(8) << endl;
    swapInts(a, b);
    cout << "After swap: a = " << a << ", b = " << b << endl;
    return 0;
}