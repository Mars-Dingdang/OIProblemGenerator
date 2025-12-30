#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Convert decimal integer to any base (2-16)
string decimal_to_base(int num, int base) {
    if (num == 0) return "0";
    
    string digits = "0123456789ABCDEF";
    string result = "";
    bool negative = num < 0;
    num = abs(num);
    
    while (num > 0) {
        result += digits[num % base];
        num /= base;
    }
    
    if (negative) result += "-";
    reverse(result.begin(), result.end());
    return result;
}

// Convert from any base (2-16) to decimal
int base_to_decimal(string s, int base) {
    int result = 0;
    bool negative = false;
    
    if (s[0] == '-') {
        negative = true;
        s = s.substr(1);
    }
    
    for (char c : s) {
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
        else throw invalid_argument("Invalid digit");
        
        if (digit >= base) throw invalid_argument("Digit exceeds base");
        
        result = result * base + digit;
    }
    
    return negative ? -result : result;
}

// Convert decimal fraction to binary (for demonstration)
string decimal_fraction_to_binary(double fraction, int precision = 10) {
    if (fraction == 0.0) return "0";
    
    string result = "0.";
    while (fraction > 0 && precision-- > 0) {
        fraction *= 2;
        if (fraction >= 1.0) {
            result += "1";
            fraction -= 1.0;
        } else {
            result += "0";
        }
    }
    return result;
}

int main() {
    // Example usage
    cout << decimal_to_base(35, 2) << endl;      // 100011
    cout << decimal_to_base(35, 8) << endl;      // 43
    cout << decimal_to_base(35, 16) << endl;     // 23
    
    cout << base_to_decimal("100011", 2) << endl; // 35
    cout << base_to_decimal("43", 8) << endl;     // 35
    cout << base_to_decimal("23", 16) << endl;    // 35
    
    cout << decimal_fraction_to_binary(0.25) << endl; // 0.01
    
    return 0;
}