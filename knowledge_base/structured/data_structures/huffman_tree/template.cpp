#include <vector>
#include <queue>
#include <functional>

struct HNode {
    int weight;
    HNode *lchild, *rchild;
    HNode(int w) : weight(w), lchild(nullptr), rchild(nullptr) {}
};

using Htree = HNode*;

Htree buildHuffmanTree(std::vector<int>& weights) {
    auto cmp = [](Htree a, Htree b) { return a->weight > b->weight; };
    std::priority_queue<Htree, std::vector<Htree>, decltype(cmp)> pq(cmp);
    
    for (int w : weights) {
        pq.push(new HNode(w));
    }
    
    while (pq.size() > 1) {
        Htree left = pq.top(); pq.pop();
        Htree right = pq.top(); pq.pop();
        
        Htree root = new HNode(left->weight + right->weight);
        root->lchild = left;
        root->rchild = right;
        
        pq.push(root);
    }
    
    return pq.empty() ? nullptr : pq.top();
}