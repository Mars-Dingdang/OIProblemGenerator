#include <iostream>
#include <vector>
using namespace std;

class StackWithMultiPop {
private:
    vector<int> stk;
public:
    void push(int x) {
        stk.push_back(x);
    }
    void pop() {
        if (!stk.empty()) stk.pop_back();
    }
    void multi_pop(int k) {
        int cnt = min(k, (int)stk.size());
        for (int i = 0; i < cnt; ++i) {
            stk.pop_back();
        }
    }
    int size() const { return stk.size(); }
};

int main() {
    // Example usage: amortized analysis ensures average O(1) per operation.
    StackWithMultiPop s;
    s.push(1);
    s.push(2);
    s.multi_pop(2);
    s.push(3);
    s.pop();
    return 0;
}