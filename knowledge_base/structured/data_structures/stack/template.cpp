#include <stack>
#include <vector>
#include <deque>
#include <list>

// 数组模拟栈（使用st[0]存储栈大小）
template<typename T, int N>
struct ArrayStack {
    T st[N];
    int size() { return st[0]; }
    bool empty() { return st[0] == 0; }
    void push(T x) { st[++st[0]] = x; }
    void pop() { if(st[0]) --st[0]; }
    T top() { return st[st[0]]; }
    void clear() { st[0] = 0; }
};

// STL栈使用示例
void stl_stack_example() {
    // 默认使用deque作为底层容器
    std::stack<int> s1;
    
    // 使用vector作为底层容器
    std::stack<int, std::vector<int>> s2;
    
    // 使用list作为底层容器
    std::stack<int, std::list<int>> s3;
    
    // 基本操作
    s1.push(10);           // 压栈
    int top = s1.top();    // 取栈顶
    s1.pop();              // 弹栈
    bool empty = s1.empty(); // 判空
    size_t sz = s1.size(); // 大小
}

// 最小栈实现（支持O(1)获取当前最小值）
template<typename T>
class MinStack {
private:
    std::stack<T> data;
    std::stack<T> min_stack;
public:
    void push(T x) {
        data.push(x);
        if(min_stack.empty() || x <= min_stack.top()) {
            min_stack.push(x);
        }
    }
    void pop() {
        if(data.empty()) return;
        if(data.top() == min_stack.top()) {
            min_stack.pop();
        }
        data.pop();
    }
    T top() { return data.top(); }
    T getMin() { return min_stack.top(); }
    bool empty() { return data.empty(); }
    size_t size() { return data.size(); }
};