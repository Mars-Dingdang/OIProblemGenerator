#include <algorithm>
#include <memory>
#include <vector>

template <class Key, class Compare = std::less<Key>>
class Set {
 private:
  enum NodeColor { kBlack = 0, kRed = 1 };

  struct Node {
    Key key;
    Node *lc{nullptr}, *rc{nullptr};
    size_t size{1};
    NodeColor color;

    Node(Key k, NodeColor c) : key(k), color(c) {}
  };

  Compare cmp_;
  Node* root_ = nullptr;

  bool is_red(Node* node) const {
    return node != nullptr && node->color == kRed;
  }

  size_t size(Node* node) const {
    return node ? node->size : 0;
  }

  void update_size(Node* node) {
    if (node) node->size = size(node->lc) + size(node->rc) + 1;
  }

  Node* rotate_left(Node* h) {
    Node* x = h->rc;
    h->rc = x->lc;
    x->lc = h;
    x->color = h->color;
    h->color = kRed;
    x->size = h->size;
    update_size(h);
    return x;
  }

  Node* rotate_right(Node* h) {
    Node* x = h->lc;
    h->lc = x->rc;
    x->rc = h;
    x->color = h->color;
    h->color = kRed;
    x->size = h->size;
    update_size(h);
    return x;
  }

  void color_flip(Node* node) {
    node->color = static_cast<NodeColor>(!node->color);
    if (node->lc) node->lc->color = static_cast<NodeColor>(!node->lc->color);
    if (node->rc) node->rc->color = static_cast<NodeColor>(!node->rc->color);
  }

  Node* insert(Node* h, const Key& key) {
    if (!h) return new Node(key, kRed);

    if (key == h->key) {
      // do nothing
    } else if (cmp_(key, h->key)) {
      h->lc = insert(h->lc, key);
    } else {
      h->rc = insert(h->rc, key);
    }

    return fix_up(h);
  }

  Node* fix_up(Node* h) {
    if (is_red(h->rc) && !is_red(h->lc)) h = rotate_left(h);
    if (is_red(h->lc) && is_red(h->lc->lc)) h = rotate_right(h);
    if (is_red(h->lc) && is_red(h->rc)) color_flip(h);
    update_size(h);
    return h;
  }

  Node* move_red_left(Node* h) {
    color_flip(h);
    if (h->rc && is_red(h->rc->lc)) {
      h->rc = rotate_right(h->rc);
      h = rotate_left(h);
      color_flip(h);
    }
    return h;
  }

  Node* delete_min(Node* h) {
    if (!h->lc) {
      delete h;
      return nullptr;
    }
    if (!is_red(h->lc) && !is_red(h->lc->lc)) {
      h = move_red_left(h);
    }
    h->lc = delete_min(h->lc);
    return fix_up(h);
  }

  Node* move_red_right(Node* h) {
    color_flip(h);
    if (h->lc && is_red(h->lc->lc)) {
      h = rotate_right(h);
      color_flip(h);
    }
    return h;
  }

  Node* delete_arbitrary(Node* h, const Key& key) {
    if (cmp_(key, h->key)) {
      if (h->lc && !is_red(h->lc) && h->lc->lc && !is_red(h->lc->lc)) {
        h = move_red_left(h);
      }
      h->lc = delete_arbitrary(h->lc, key);
    } else {
      if (is_red(h->lc)) h = rotate_right(h);
      if (key == h->key && !h->rc) {
        delete h;
        return nullptr;
      }
      if (h->rc && !is_red(h->rc) && h->rc->lc && !is_red(h->rc->lc)) {
        h = move_red_right(h);
      }
      if (key == h->key) {
        Node* min_node = h->rc;
        while (min_node->lc) min_node = min_node->lc;
        h->key = min_node->key;
        h->rc = delete_min(h->rc);
      } else {
        h->rc = delete_arbitrary(h->rc, key);
      }
    }
    return fix_up(h);
  }

 public:
  void insert(const Key& key) {
    root_ = insert(root_, key);
    if (root_) root_->color = kBlack;
  }

  void erase(const Key& key) {
    if (!root_) return;
    if (!is_red(root_->lc) && !is_red(root_->rc)) {
      root_->color = kRed;
    }
    root_ = delete_arbitrary(root_, key);
    if (root_) root_->color = kBlack;
  }

  size_t size() const { return size(root_); }

  bool empty() const { return !root_; }

  ~Set() { destroyTree(root_); }

  void destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->lc);
    destroyTree(node->rc);
    delete node;
  }
};