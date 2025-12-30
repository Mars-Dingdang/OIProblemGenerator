struct Node {
    int value;
    Node* next;
    Node* prev;
    Node(int val = 0) : value(val), next(nullptr), prev(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insert_front(int val) {
        Node* new_node = new Node(val);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }

    void insert_back(int val) {
        Node* new_node = new Node(val);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size++;
    }

    void insert_after(Node* node, int val) {
        if (!node) return;
        Node* new_node = new Node(val);
        new_node->next = node->next;
        new_node->prev = node;
        if (node->next) node->next->prev = new_node;
        node->next = new_node;
        if (node == tail) tail = new_node;
        size++;
    }

    void delete_node(Node* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
        delete node;
        size--;
    }

    Node* find(int val) {
        Node* curr = head;
        while (curr) {
            if (curr->value == val) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    int get_size() { return size; }

    bool empty() { return size == 0; }

    ~LinkedList() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};