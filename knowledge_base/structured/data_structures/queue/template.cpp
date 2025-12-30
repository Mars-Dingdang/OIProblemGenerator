#include <queue>
#include <iostream>
using namespace std;

int main() {
    queue<int> q;
    // 入队
    q.push(1);
    q.push(2);
    q.push(3);
    // 访问队首
    cout << q.front() << endl; // 1
    // 出队
    q.pop();
    cout << q.front() << endl; // 2
    // 大小
    cout << q.size() << endl; // 2
    // 是否为空
    cout << q.empty() << endl; // 0 (false)
    return 0;
}