struct Node {
  long long v;
  Node *child, *sibling;
  
  Node(long long val) : v(val), child(nullptr), sibling(nullptr) {}
};

Node* meld(Node* x, Node* y) {
  if (!x) return y;
  if (!y) return x;
  if (x->v > y->v) std::swap(x, y);
  y->sibling = x->child;
  x->child = y;
  return x;
}

Node* merges(Node* x) {
  if (!x || !x->sibling) return x;
  Node* y = x->sibling;
  Node* c = y->sibling;
  x->sibling = y->sibling = nullptr;
  return meld(merges(c), meld(x, y));
}

Node* delete_min(Node* x) {
  Node* new_root = merges(x->child);
  delete x;
  return new_root;
}

// With parent pointer for decrease_key
struct NodeWithParent {
  long long v;
  NodeWithParent *child, *sibling, *father;
  
  NodeWithParent(long long val) : v(val), child(nullptr), sibling(nullptr), father(nullptr) {}
};

NodeWithParent* meld_p(NodeWithParent* x, NodeWithParent* y) {
  if (!x) return y;
  if (!y) return x;
  if (x->v > y->v) std::swap(x, y);
  if (x->child) x->child->father = y;
  y->sibling = x->child;
  y->father = x;
  x->child = y;
  return x;
}

NodeWithParent* merges_p(NodeWithParent* x) {
  if (!x) return nullptr;
  x->father = nullptr;
  if (!x->sibling) return x;
  NodeWithParent* y = x->sibling;
  NodeWithParent* c = y->sibling;
  y->father = nullptr;
  x->sibling = y->sibling = nullptr;
  return meld_p(merges_p(c), meld_p(x, y));
}

NodeWithParent* decrease_key(NodeWithParent* root, NodeWithParent* x, long long v) {
  x->v = v;
  if (x == root) return root;
  if (x->father->child == x) {
    x->father->child = x->sibling;
  } else {
    x->father->sibling = x->sibling;
  }
  if (x->sibling) {
    x->sibling->father = x->father;
  }
  x->sibling = nullptr;
  x->father = nullptr;
  return meld_p(root, x);
}