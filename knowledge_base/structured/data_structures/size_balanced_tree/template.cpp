#include <iostream>
#include <memory>
#include <functional>
#include <stack>

template<typename Key, typename Value, typename Compare = std::less<Key>>
class SizeBalancedTreeMap {
private:
    using USize = size_t;
    Compare compare;

    struct Node {
        using Ptr = std::shared_ptr<Node>;
        Key key;
        Value value;
        Ptr left = nullptr, right = nullptr;
        USize size = 1;

        explicit Node(Key k) : key(std::move(k)) {}
        explicit Node(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}

        bool isLeaf() const noexcept {
            return !left && !right;
        }

        void updateSize() {
            USize leftSize = left ? left->size : 0;
            USize rightSize = right ? right->size : 0;
            size = leftSize + rightSize + 1;
        }

        static Ptr from(const Key& k) {
            return std::make_shared<Node>(Node(k));
        }

        static Ptr from(const Key& k, const Value& v) {
            return std::make_shared<Node>(Node(k, v));
        }
    };

    using NodePtr = typename Node::Ptr;
    NodePtr root;

    void rotateLeft(NodePtr& node) {
        NodePtr successor = node->right;
        node->right = successor->left;
        successor->left = node;
        node->updateSize();
        successor->updateSize();
        node = successor;
    }

    void rotateRight(NodePtr& node) {
        NodePtr successor = node->left;
        node->left = successor->right;
        successor->right = node;
        node->updateSize();
        successor->updateSize();
        node = successor;
    }

    void fixBalance(NodePtr& node) {
        if (!node) return;
        bool done = false;
        if (node->left && node->right) {
            if (node->right->left && size(node->right->left) > size(node->left)) {
                rotateRight(node->right);
                rotateLeft(node);
                fixBalance(node->left);
                fixBalance(node->right);
            } else if (node->right->right && size(node->right->right) > size(node->left)) {
                rotateLeft(node);
                fixBalance(node->left);
            } else if (node->left->left && size(node->left->left) > size(node->right)) {
                rotateRight(node);
                fixBalance(node->right);
            } else if (node->left->right && size(node->left->right) > size(node->right)) {
                rotateLeft(node->left);
                rotateRight(node);
                fixBalance(node->left);
                fixBalance(node->right);
            } else {
                done = true;
            }
        } else if (node->left && size(node->left) > size(node->right) + 1) {
            if (size(node->left->left) > size(node->right)) {
                rotateRight(node);
            } else if (node->left->right && size(node->left->right) > size(node->right)) {
                rotateLeft(node->left);
                rotateRight(node);
            } else {
                done = true;
            }
        } else if (node->right && size(node->right) > size(node->left) + 1) {
            if (size(node->right->right) > size(node->left)) {
                rotateLeft(node);
            } else if (node->right->left && size(node->right->left) > size(node->left)) {
                rotateRight(node->right);
                rotateLeft(node);
            } else {
                done = true;
            }
        } else {
            done = true;
        }
        if (!done) fixBalance(node);
    }

    USize size(const NodePtr& node) const {
        return node ? node->size : 0;
    }

    void insert(NodePtr& node, const Key& key, const Value& value, bool replace = true) {
        if (!node) {
            node = Node::from(key, value);
            return;
        }
        if (compare(key, node->key)) {
            if (!node->left) {
                node->left = Node::from(key, value);
            } else {
                insert(node->left, key, value, replace);
            }
        } else if (compare(node->key, key)) {
            if (!node->right) {
                node->right = Node::from(key, value);
            } else {
                insert(node->right, key, value, replace);
            }
        } else {
            if (replace) node->value = value;
            return;
        }
        node->updateSize();
        fixBalance(node);
    }

    bool remove(NodePtr& node, const Key& key) {
        if (!node) return false;
        if (compare(key, node->key)) {
            if (remove(node->left, key)) {
                node->updateSize();
                fixBalance(node);
                return true;
            }
            return false;
        } else if (compare(node->key, key)) {
            if (remove(node->right, key)) {
                node->updateSize();
                fixBalance(node);
                return true;
            }
            return false;
        } else {
            if (node->isLeaf()) {
                node = nullptr;
            } else if (!node->right) {
                node = node->left;
            } else if (!node->left) {
                node = node->right;
            } else if (!node->right->left) {
                NodePtr right = node->right;
                right->left = node->left;
                right->updateSize();
                node = right;
                fixBalance(node);
            } else {
                std::stack<NodePtr> path;
                NodePtr successor = node->right;
                NodePtr parent = node;
                path.push(node);
                while (successor->left) {
                    path.push(successor);
                    parent = successor;
                    successor = successor->left;
                }
                std::swap(node->key, successor->key);
                std::swap(node->value, successor->value);
                parent->left = successor->right;
                while (!path.empty()) {
                    path.top()->updateSize();
                    path.pop();
                }
                fixBalance(root);
            }
            return true;
        }
    }

    USize countLess(ConstNodePtr node, const Key& key, bool countEqual = false) const {
        if (!node) return 0;
        if (compare(key, node->key)) {
            return countLess(node->left, key, countEqual);
        } else if (compare(node->key, key)) {
            return size(node->left) + 1 + countLess(node->right, key, countEqual);
        } else {
            return size(node->left) + (countEqual ? 1 : 0);
        }
    }

public:
    SizeBalancedTreeMap() : root(nullptr) {}

    void insert(const Key& key, const Value& value, bool replace = true) {
        insert(root, key, value, replace);
    }

    bool remove(const Key& key) {
        return remove(root, key);
    }

    USize rank(const Key& key, bool countEqual = false) const {
        return countLess(root, key, countEqual);
    }

    bool contains(const Key& key) const {
        return find(root, key) != nullptr;
    }

    size_t size() const {
        return root ? root->size : 0;
    }

    bool empty() const {
        return !root;
    }

    void clear() {
        root = nullptr;
    }
};