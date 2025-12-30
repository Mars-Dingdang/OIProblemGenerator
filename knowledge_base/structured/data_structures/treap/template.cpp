struct Node {
  Node *ch[2];
  int val, rank;
  int rep_cnt;
  int siz;

  Node(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
  }

  void upd_siz() {
    siz = rep_cnt;
    if (ch[0]) siz += ch[0]->siz;
    if (ch[1]) siz += ch[1]->siz;
  }
};

typedef Node* pnode;

enum rot_type { LF = 1, RT = 0 };

void _rotate(pnode &cur, rot_type dir) {
  pnode tmp = cur->ch[dir];
  cur->ch[dir] = tmp->ch[!dir];
  tmp->ch[!dir] = cur;
  cur->upd_siz();
  tmp->upd_siz();
  cur = tmp;
}

void _insert(pnode &cur, int val) {
  if (!cur) {
    cur = new Node(val);
    return;
  }
  if (val == cur->val) {
    cur->rep_cnt++;
    cur->siz++;
    return;
  }
  bool dir = val > cur->val;
  _insert(cur->ch[dir], val);
  if (cur->ch[dir]->rank < cur->rank) {
    _rotate(cur, (rot_type)dir);
  }
  cur->upd_siz();
}

void _del(pnode &cur, int val) {
  if (!cur) return;
  if (val > cur->val) {
    _del(cur->ch[1], val);
    cur->upd_siz();
  } else if (val < cur->val) {
    _del(cur->ch[0], val);
    cur->upd_siz();
  } else {
    if (cur->rep_cnt > 1) {
      cur->rep_cnt--;
      cur->siz--;
      return;
    }
    uint8_t state = 0;
    state |= (cur->ch[0] != nullptr);
    state |= ((cur->ch[1] != nullptr) << 1);
    pnode tmp = cur;
    switch (state) {
      case 0:
        delete cur;
        cur = nullptr;
        break;
      case 1:
        cur = tmp->ch[0];
        delete tmp;
        break;
      case 2:
        cur = tmp->ch[1];
        delete tmp;
        break;
      case 3: {
        rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
        _rotate(cur, dir);
        _del(cur->ch[!dir], val);
        cur->upd_siz();
        break;
      }
    }
  }
}

int _query_rank(pnode cur, int val) {
  if (!cur) return 1;
  int left_siz = cur->ch[0] ? cur->ch[0]->siz : 0;
  if (val == cur->val) return left_siz + 1;
  if (val < cur->val) return _query_rank(cur->ch[0], val);
  return left_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
}

int _query_val(pnode cur, int rank) {
  int left_siz = cur->ch[0] ? cur->ch[0]->siz : 0;
  if (rank <= left_siz) return _query_val(cur->ch[0], rank);
  if (rank <= left_siz + cur->rep_cnt) return cur->val;
  return _query_val(cur->ch[1], rank - left_siz - cur->rep_cnt);
}

int q_prev_tmp = -1;
int _query_prev(pnode cur, int val) {
  if (!cur) return q_prev_tmp;
  if (val <= cur->val) {
    if (cur->ch[0]) return _query_prev(cur->ch[0], val);
  } else {
    q_prev_tmp = cur->val;
    if (cur->ch[1]) _query_prev(cur->ch[1], val);
    return q_prev_tmp;
  }
  return q_prev_tmp;
}

int q_nex_tmp = -1;
int _query_nex(pnode cur, int val) {
  if (!cur) return q_nex_tmp;
  if (val >= cur->val) {
    if (cur->ch[1]) return _query_nex(cur->ch[1], val);
  } else {
    q_nex_tmp = cur->val;
    if (cur->ch[0]) _query_nex(cur->ch[0], val);
    return q_nex_tmp;
  }
  return q_nex_tmp;
}