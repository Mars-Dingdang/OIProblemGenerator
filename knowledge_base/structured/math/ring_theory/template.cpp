// Ring theory is a theoretical algebraic framework; no standard C++ template exists.
// However, for illustration, here is a simple structure for a commutative ring with ideals.
#include <vector>
#include <set>
#include <iostream>

// Example: Representing an ideal in Z (integers) as multiples of n.
struct Ideal {
    long long generator; // For principal ideal in Z
    Ideal(long long n) : generator(n) {}
    bool contains(long long x) const {
        return x % generator == 0;
    }
};

// Example: Quotient ring Z/nZ
struct QuotientRing {
    long long modulus;
    QuotientRing(long long n) : modulus(n) {}
    long long add(long long a, long long b) const {
        return (a + b) % modulus;
    }
    long long mul(long long a, long long b) const {
        return (a * b) % modulus;
    }
};

int main() {
    Ideal I(6); // ideal 6Z
    std::cout << "12 in I? " << I.contains(12) << std::endl; // 1
    std::cout << "7 in I? " << I.contains(7) << std::endl;   // 0

    QuotientRing Zmod5(5);
    std::cout << "3 + 4 mod 5 = " << Zmod5.add(3, 4) << std::endl; // 2
    std::cout << "3 * 4 mod 5 = " << Zmod5.mul(3, 4) << std::endl; // 2
    return 0;
}