#include <vector>
#include <cmath>
using namespace std;

const int N = 1000000; // adjust as needed
vector<int> prime;
bool is_prime[N + 1];

// Basic Eratosthenes sieve
void eratosthenes(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    prime.clear();
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) prime.push_back(i);
    }
}

// Linear sieve (Euler sieve) with Euler's totient function
int phi[N + 1];
void linear_sieve(int n) {
    vector<int> pri;
    vector<bool> not_prime(n + 1, false);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : pri) {
            if (i * p > n) break;
            not_prime[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
}