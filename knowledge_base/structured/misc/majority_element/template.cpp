#include <vector>
using namespace std;

// 求出现次数 > n/2 的主元素
int majorityElement(vector<int>& nums) {
    int val = 0, cnt = 0;
    for (int x : nums) {
        if (cnt == 0) val = x;
        (x == val) ? ++cnt : --cnt;
    }
    return val;
}

// 验证主元素是否真的存在
bool validate(vector<int>& nums, int candidate) {
    int count = 0;
    for (int x : nums) if (x == candidate) ++count;
    return count > nums.size() / 2;
}