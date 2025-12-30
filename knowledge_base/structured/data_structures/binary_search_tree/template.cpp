struct TreeNode {
  int key;
  TreeNode* left;
  TreeNode* right;
  int size;   // 子树大小
  int count;  // 重复元素个数

  TreeNode(int value)
      : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
};

// 中序遍历
void inorderTraversal(TreeNode* root) {
  if (root == nullptr) return;
  inorderTraversal(root->left);
  std::cout << root->key << " ";
  inorderTraversal(root->right);
}

// 查找最小值
int findMin(TreeNode* root) {
  if (root == nullptr) return -1;
  while (root->left != nullptr) root = root->left;
  return root->key;
}

// 查找最大值
int findMax(TreeNode* root) {
  if (root == nullptr) return -1;
  while (root->right != nullptr) root = root->right;
  return root->key;
}

// 搜索节点
bool search(TreeNode* root, int target) {
  if (root == nullptr) return false;
  if (root->key == target) return true;
  else if (target < root->key) return search(root->left, target);
  else return search(root->right, target);
}

// 插入节点
TreeNode* insert(TreeNode* root, int value) {
  if (root == nullptr) return new TreeNode(value);
  if (value < root->key) {
    root->left = insert(root->left, value);
  } else if (value > root->key) {
    root->right = insert(root->right, value);
  } else {
    root->count++;
  }
  root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
  return root;
}

// 删除节点
TreeNode* remove(TreeNode* root, int value) {
  if (root == nullptr) return root;
  if (value < root->key) {
    root->left = remove(root->left, value);
  } else if (value > root->key) {
    root->right = remove(root->right, value);
  } else {
    if (root->count > 1) {
      root->count--;
    } else {
      if (root->left == nullptr) {
        TreeNode* temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        TreeNode* temp = root->left;
        delete root;
        return temp;
      } else {
        TreeNode* successor = findMinNode(root->right);
        root->key = successor->key;
        root->count = successor->count;
        successor->count = 1;
        root->right = remove(root->right, successor->key);
      }
    }
  }
  root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
  return root;
}

// 辅助函数：查找右子树中的最小节点
TreeNode* findMinNode(TreeNode* root) {
  while (root && root->left != nullptr) root = root->left;
  return root;
}

// 查询值v的排名（升序中第一个v前的元素个数+1）
int queryRank(TreeNode* root, int v) {
  if (root == nullptr) return 0;
  if (root->key == v) return (root->left ? root->left->size : 0) + 1;
  if (root->key > v) return queryRank(root->left, v);
  return queryRank(root->right, v) + (root->left ? root->left->size : 0) + root->count;
}

// 查询第k小的元素
int querykth(TreeNode* root, int k) {
  if (root == nullptr) return -1;
  int leftSize = root->left ? root->left->size : 0;
  if (k <= leftSize) return querykth(root->left, k);
  if (k <= leftSize + root->count) return root->key;
  return querykth(root->right, k - leftSize - root->count);
}

// 左旋
TreeNode* rotateLeft(TreeNode* root) {
  TreeNode* newRoot = root->right;
  root->right = newRoot->left;
  newRoot->left = root;
  // updateHeight(root); // 若维护高度
  // updateHeight(newRoot);
  return newRoot;
}

// 右旋
TreeNode* rotateRight(TreeNode* root) {
  TreeNode* newRoot = root->left;
  root->left = newRoot->right;
  newRoot->right = root;
  // updateHeight(root);
  // updateHeight(newRoot);
  return newRoot;
}