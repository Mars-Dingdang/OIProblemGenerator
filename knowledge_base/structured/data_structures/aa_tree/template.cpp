#include <iostream>
#include <memory>

struct AANode {
    int key;
    int level;
    std::shared_ptr<AANode> left, right;

    AANode(int k) : key(k), level(1), left(nullptr), right(nullptr) {}
};

class AATree {
public:
    std::shared_ptr<AANode> root;

    AATree() : root(nullptr) {}

    void rotate_left(std::shared_ptr<AANode>& node) {
        auto new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        new_root->level++;
        node = new_root;
    }

    void rotate_right(std::shared_ptr<AANode>& node) {
        auto new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        node = new_root;
    }

    void skew(std::shared_ptr<AANode>& node) {
        if (node && node->left && node->left->level == node->level) {
            rotate_right(node);
        }
    }

    void split(std::shared_ptr<AANode>& node) {
        if (node && node->right && node->right->right &&
            node->right->right->level == node->level) {
            rotate_left(node);
        }
    }

    void insert(std::shared_ptr<AANode>& node, int key) {
        if (!node) {
            node = std::make_shared<AANode>(key);
            return;
        }

        if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        }
        // Duplicates ignored

        skew(node);
        split(node);
    }

    std::shared_ptr<AANode> find_min(std::shared_ptr<AANode> node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void delete_key(std::shared_ptr<AANode>& node, int key) {
        if (!node) return;

        if (key < node->key) {
            delete_key(node->left, key);
        } else if (key > node->key) {
            delete_key(node->right, key);
        } else {
            if (!node->left || !node->right) {
                auto child = node->left ? node->left : node->right;
                *node = *child;  // Copy child data
            } else {
                auto successor = find_min(node->right);
                node->key = successor->key;
                delete_key(node->right, successor->key);
            }
        }

        if (node && (node->left && node->left->level < node->level - 1 ||
                     node->right && node->right->level < node->level - 1)) {
            if (node->right) node->right->level = node->level - 1;
            skew(node);
            if (node->right) skew(node->right);
            if (node->right && node->right->right)
                skew(node->right->right);
            split(node);
            if (node->right) split(node->right);
        }
    }
};