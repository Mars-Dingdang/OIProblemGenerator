#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <sstream>

using i64 = int64_t;
using u64 = uint64_t;

static std::mt19937 rng_;

struct Node {
  int size_;
  int priority_;
  Node* left_;
  Node* right_;
  Node* parent_;
  int from_;
  int to_;

  Node(int from, int to)
      : size_(1),
        priority_(rng_()),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        from_(from),
        to_(to) {}

  void Maintain() {
    size_ = 1;
    if (left_) {
      size_ += left_->size_;
      left_->parent_ = this;
    }
    if (right_) {
      size_ += right_->size_;
      right_->parent_ = this;
    }
  }
};

static int GetSize(Node* p) { return p == nullptr ? 0 : p->size_; }

static Node* FindRoot(Node* p) {
  if (!p) return nullptr;
  while (p->parent_ != nullptr) p = p->parent_;
  return p;
}

Node* AllocateNode(int u, int v) {
  Node* p = new Node(u, v);
  return p;
}

void FreeNode(Node*& p) {
  if (p) {
    delete p;
    p = nullptr;
  }
}

class Treap {
 public:
  static Node* Merge(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->priority_ < b->priority_) {
      a->right_ = Merge(a->right_, b);
      a->Maintain();
      return a;
    } else {
      b->left_ = Merge(a, b->left_);
      b->Maintain();
      return b;
    }
  }

  static int GetPosition(Node* p) {
    assert(p != nullptr);
    int position = GetSize(p->left_) + 1;
    Node* cur = p;
    while (cur) {
      if (cur->parent_ && cur == cur->parent_->right_) {
        position += GetSize(cur->parent_->left_) + 1;
      }
      cur = cur->parent_;
    }
    return position;
  }

  static std::pair<Node*, Node*> SplitUp2(Node* p) {
    assert(p != nullptr);
    Node *a = nullptr, *b = nullptr;
    b = p->right_;
    if (b) b->parent_ = nullptr;
    p->right_ = nullptr;

    bool is_p_left_child_of_parent = false;
    bool is_from_left_child = false;
    while (p) {
      Node* parent = p->parent_;
      if (parent) {
        is_p_left_child_of_parent = (parent->left_ == p);
        if (is_p_left_child_of_parent) {
          parent->left_ = nullptr;
        } else {
          parent->right_ = nullptr;
        }
        p->parent_ = nullptr;
      }

      if (!is_from_left_child) {
        a = Merge(p, a);
      } else {
        b = Merge(b, p);
      }

      is_from_left_child = is_p_left_child_of_parent;
      p->Maintain();
      p = parent;
    }
    return {a, b};
  }

  static std::tuple<Node*, Node*, Node*> SplitUp3(Node* p) {
    assert(p != nullptr);
    Node* a = p->left_;
    if (a) a->parent_ = nullptr;
    p->left_ = nullptr;

    Node* b = p->right_;
    if (b) b->parent_ = nullptr;
    p->right_ = nullptr;

    Node* c = p;

    bool is_p_left_child_of_parent = false;
    bool is_from_left_child = false;
    Node* parent = p->parent_;
    if (parent) {
      is_p_left_child_of_parent = (parent->left_ == p);
      if (is_p_left_child_of_parent) {
        parent->left_ = nullptr;
      } else {
        parent->right_ = nullptr;
      }
      p->parent_ = nullptr;
    }
    is_from_left_child = is_p_left_child_of_parent;
    p->Maintain();
    p = parent;

    while (p) {
      Node* parent = p->parent_;
      if (parent) {
        is_p_left_child_of_parent = (parent->left_ == p);
        if (is_p_left_child_of_parent) {
          parent->left_ = nullptr;
        } else {
          parent->right_ = nullptr;
        }
        p->parent_ = nullptr;
      }

      if (!is_from_left_child) {
        a = Merge(p, a);
      } else {
        b = Merge(b, p);
      }

      is_from_left_child = is_p_left_child_of_parent;
      p->Maintain();
      p = parent;
    }
    return {a, c, b};
  }
};

class DynamicForest {
 private:
  int n_;
  std::vector<Node*> vertices_;
  std::vector<std::map<int, Node*>> tree_edges_;

 public:
  DynamicForest(int n) : n_(n), vertices_(n_), tree_edges_(n_) {
    assert(n_ > 0);
    for (int i = 0; i < n_; ++i) vertices_[i] = AllocateNode(i, i);
  }

  void MakeRoot(int u) {
    Node* vertex_u = vertices_[u];
    auto [L1, L2] = Treap::SplitUp2(vertex_u);
    Treap::Merge(L2, L1);
  }

  void Insert(int u, int v) {
    Node* vertex_u = vertices_[u];
    Node* vertex_v = vertices_[v];
    Node* edge_uv = AllocateNode(u, v);
    Node* edge_vu = AllocateNode(v, u);
    tree_edges_[u][v] = edge_uv;
    tree_edges_[v][u] = edge_vu;

    auto [L11, L12] = Treap::SplitUp2(vertex_u);
    auto [L21, L22] = Treap::SplitUp2(vertex_v);

    Node* L = L12;
    L = Treap::Merge(L, L11);
    L = Treap::Merge(L, edge_uv);
    L = Treap::Merge(L, L22);
    L = Treap::Merge(L, L21);
    L = Treap::Merge(L, edge_vu);
  }

  void Delete(int u, int v) {
    Node* edge_uv = tree_edges_[u][v];
    Node* edge_vu = tree_edges_[v][u];
    tree_edges_[u].erase(v);
    tree_edges_[v].erase(u);

    int position_uv = Treap::GetPosition(edge_uv);
    int position_vu = Treap::GetPosition(edge_vu);
    if (position_uv > position_vu) {
      std::swap(edge_uv, edge_vu);
      std::swap(position_uv, position_vu);
    }

    auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
    auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
    Treap::Merge(L1, L3);

    FreeNode(edge_uv);
    FreeNode(edge_vu);
  }

  bool IsConnected(int u, int v) {
    return FindRoot(vertices_[u]) == FindRoot(vertices_[v]);
  }
};