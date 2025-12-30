// This is a conceptual C++ translation of the functional Finger Tree
// Due to the functional nature and complexity, a full implementation is non-trivial in C++
// Below is a simplified framework outlining core ideas

#include <memory>
#include <variant>
#include <vector>

template<typename T>
struct Node {
    std::vector<T> values;
};

template<typename T>
struct Digit {
    std::vector<T> entries;
    Digit(std::initializer_list<T> list) : entries(list) {}
};

template<typename T>
class FingerTree {
public:
    virtual ~FingerTree() = default;
    virtual bool isEmpty() const = 0;
};

template<typename T>
struct Empty : FingerTree<T> {
    bool isEmpty() const override { return true; }
};

template<typename T>
struct Single : FingerTree<T> {
    T value;
    Single(T v) : value(v) {}
    bool isEmpty() const override { return false; }
};

template<typename T>
struct Deep : FingerTree<T> {
    Digit<T> prefix;
    std::shared_ptr<FingerTree<Node<T>>> spine;
    Digit<T> suffix;

    Deep(Digit<T> pre, std::shared_ptr<FingerTree<Node<T>>> sp, Digit<T> suf)
        : prefix(pre), spine(sp), suffix(suf) {}

    bool isEmpty() const override { return false; }
};

// Supported operations would be implemented as functions
// e.g., push front/back, split, append, etc.
// Note: Full implementation requires lazy evaluation and monoidal annotations for efficiency
