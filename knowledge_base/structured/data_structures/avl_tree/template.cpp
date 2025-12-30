#ifndef AVLTREE_MAP_HPP
#define AVLTREE_MAP_HPP

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Compare = std::less<Key>>
class AvlTreeMap {
 private:
  using USize = size_t;
  using Factor = int64_t;

  Compare compare = Compare();

 public:
  struct Entry {
    Key key;
    Value value;

    bool operator==(const Entry &rhs) const noexcept {
      return this->key == rhs.key && this->value == rhs.value;
    }

    bool operator!=(const Entry &rhs) const noexcept {
      return this->key != rhs.key || this->value != rhs.value;
    }
  };

 private:
  struct Node {
    using Ptr = std::shared_ptr<Node>;
    using Provider = const std::function<Ptr(void)> &;
    using Consumer = const std::function<void(const Ptr &)> &;

    Key key;
    Value value{};
    Ptr left = nullptr;
    Ptr right = nullptr;
    USize height = 1;

    explicit Node(Key k) : key(std::move(k)) {}
    explicit Node(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}

    ~Node() = default;

    inline bool isLeaf() const noexcept {
      return this->left == nullptr && this->right == nullptr;
    }

    inline void updateHeight() noexcept {
      if (this->isLeaf()) {
        this->height = 1;
      } else if (this->left == nullptr) {
        this->height = this->right->height + 1;
      } else if (this->right == nullptr) {
        this->height = this->left->height + 1;
      } else {
        this->height = std::max(left->height, right->height) + 1;
      }
    }

    inline Factor factor() const noexcept {
      if (this->isLeaf()) {
        return 0;
      } else if (this->left == nullptr) {
        return (Factor)this->right->height;
      } else if (this->right == nullptr) {
        return (Factor)-this->left->height;
      } else {
        return (Factor)(this->right->height - this->left->height);
      }
    }

    inline Entry entry() const { return Entry{key, value}; }

    static Ptr from(const Key &k) { return std::make_shared<Node>(Node(k)); }
    static Ptr from(const Key &k, const Value &v) {
      return std::make_shared<Node>(Node(k, v));
    }
  };

  using NodePtr = typename Node::Ptr;
  using ConstNodePtr = const NodePtr &;
  using NodeProvider = typename Node::Provider;
  using NodeConsumer = typename Node::Consumer;

  NodePtr root = nullptr;
  USize count = 0;

  using K = const Key &;
  using V = const Value &;

 public:
  using EntryList = std::vector<Entry>;
  using KeyValueConsumer = const std::function<void(K, V)> &;
  using MutKeyValueConsumer = const std::function<void(K, Value &)> &;
  using KeyValueFilter = const std::function<bool(K, V)> &;

  class NoSuchMappingException : protected std::exception {
   private:
    const char *message;

   public:
    explicit NoSuchMappingException(const char *msg) : message(msg) {}

    const char *what() const noexcept override { return message; }
  };

  AvlTreeMap() noexcept = default;

  inline USize size() const noexcept { return this->count; }

  inline bool empty() const noexcept { return this->count == 0; }

  void clear() noexcept {
    this->root = nullptr;
    this->count = 0;
  }

  Value get(K key) const {
    if (this->root == nullptr) {
      throw NoSuchMappingException("Invalid key");
    } else {
      NodePtr node = getNode(this->root, key);
      if (node != nullptr) {
        return node->value;
      } else {
        throw NoSuchMappingException("Invalid key");
      }
    }
  }

  Value &getOrDefault(K key) {
    if (this->root == nullptr) {
      this->root = Node::from(key);
      this->count += 1;
      return this->root->value;
    } else {
      return this
          ->getNodeOrProvide(this->root, key,
                            [&key]() { return Node::from(key); })
          ->value;
    }
  }

  bool contains(K key) const {
    return getNode(this->root, key) != nullptr;
  }

  void insert(K key, V value) {
    if (this->root == nullptr) {
      this->root = Node::from(key, value);
      this->count += 1;
    } else {
      insert(this->root, key, value);
    }
  }

  bool remove(K key) {
    if (this->root == nullptr) {
      return false;
    } else {
      return remove(this->root, key, [](ConstNodePtr) {});
    }
  }

 private:
  NodePtr getNode(ConstNodePtr node, K key) const {
    if (node == nullptr) return nullptr;
    if (key == node->key) return node;
    if (compare(key, node->key)) {
      return getNode(node->left, key);
    } else {
      return getNode(node->right, key);
    }
  }

  NodePtr &getNodeRef(NodePtr &node, K key) {
    if (key == node->key) return node;
    if (compare(key, node->key)) {
      return getNodeRef(node->left, key);
    } else {
      return getNodeRef(node->right, key);
    }
  }

  NodePtr getNodeOrProvide(NodePtr &node, K key, NodeProvider provider) {
    if (node == nullptr) {
      node = provider();
      this->count += 1;
      return node;
    } else if (key == node->key) {
      return node;
    } else if (compare(key, node->key)) {
      return getNodeOrProvide(node->left, key, provider);
    } else {
      return getNodeOrProvide(node->right, key, provider);
    }
  }

  void rotateLeft(NodePtr &p) {
    NodePtr q = p->right;
    p->right = q->left;
    q->left = p;
    p->updateHeight();
    q->updateHeight();
    p = q;
  }

  void rotateRight(NodePtr &p) {
    NodePtr q = p->left;
    p->left = q->right;
    q->right = p;
    p->updateHeight();
    q->updateHeight();
    p = q;
  }

  void maintainBalance(NodePtr &node) {
    if (!node) return;
    node->updateHeight();
    Factor bf = node->factor();
    if (bf == 2) {
      if (node->right->factor() >= 0) {
        rotateLeft(node);
      } else {
        rotateRight(node->right);
        rotateLeft(node);
      }
    } else if (bf == -2) {
      if (node->left->factor() <= 0) {
        rotateRight(node);
      } else {
        rotateLeft(node->left);
        rotateRight(node);
      }
    }
  }

  void insert(NodePtr &node, K key, V value, bool allowUpdate = true) {
    if (node == nullptr) {
      node = Node::from(key, value);
      this->count++;
      return;
    } else if (key == node->key) {
      if (allowUpdate) node->value = value;
      return;
    } else if (compare(key, node->key)) {
      insert(node->left, key, value, allowUpdate);
    } else {
      insert(node->right, key, value, allowUpdate);
    }
    maintainBalance(node);
  }

  bool remove(NodePtr &node, K key, NodeConsumer action) {
    if (node == nullptr) return false;
    if (compare(key, node->key)) {
      bool found = remove(node->left, key, action);
      if (found) maintainBalance(node);
      return found;
    } else if (compare(node->key, key)) {
      bool found = remove(node->right, key, action);
      if (found) maintainBalance(node);
      return found;
    } else {
      action(node);
      if (node->left == nullptr || node->right == nullptr) {
        node = (node->left != nullptr) ? node->left : node->right;
        this->count--;
        return true;
      } else {
        NodePtr successor = node->right;
        while (successor->left != nullptr) successor = successor->left;
        node->key = successor->key;
        node->value = successor->value;
        remove(node->right, successor->key, [](ConstNodePtr) {});
        maintainBalance(node);
        return true;
      }
    }
  }
};
#endif