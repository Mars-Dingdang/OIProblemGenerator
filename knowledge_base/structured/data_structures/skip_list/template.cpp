#include <vector>
#include <cstdlib>
#include <ctime>

const int MAX_LEVEL = 16;
const double P = 0.5;

struct Node {
    int val;
    std::vector<Node*> forward;
    Node(int v, int level) : val(v), forward(level, nullptr) {}
};

class SkipList {
public:
    Node* head;
    int level;

    SkipList() {
        level = 1;
        head = new Node(-1, MAX_LEVEL);
        srand(time(0));
    }

    int randomLevel() {
        int lvl = 1;
        while ((rand() / (double)RAND_MAX) < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    void insert(int val) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* x = head;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->val < val)
                x = x->forward[i];
            update[i] = x;
        }
        x = x->forward[0];

        if (x == nullptr || x->val != val) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level; i < newLevel; i++)
                    update[i] = head;
                level = newLevel;
            }
            Node* newNode = new Node(val, newLevel);
            for (int i = 0; i < newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    bool search(int val) {
        Node* x = head;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->val < val)
                x = x->forward[i];
        }
        x = x->forward[0];
        return x != nullptr && x->val == val;
    }

    void remove(int val) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* x = head;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->val < val)
                x = x->forward[i];
            update[i] = x;
        }
        x = x->forward[0];

        if (x != nullptr && x->val == val) {
            for (int i = 0; i < level; i++) {
                if (update[i]->forward[i] != x) break;
                update[i]->forward[i] = x->forward[i];
            }
            delete x;
            while (level > 1 && head->forward[level - 1] == nullptr)
                level--;
        }
    }

    int getKth(int k) {
        Node* x = head;
        int pos = 0;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && pos + 1 < k) {
                pos++;
                x = x->forward[i];
            }
        }
        return x->forward[0] ? x->forward[0]->val : -1;
    }
};