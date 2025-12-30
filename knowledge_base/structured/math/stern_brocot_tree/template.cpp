// In-Order Traversal of Stern-Brocot Tree up to layer N
void build(int n, int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
    if (level > n) return;
    int x = a + c, y = b + d;
    build(n, a, b, x, y, level + 1);
    std::cout << x << '/' << y << ' ';
    build(n, x, y, c, d, level + 1);
}

// Fast fraction location using continued fractions (returns vector of (count, direction))
std::vector<std::pair<int, char>> find_fraction(int x, int y) {
    std::vector<std::pair<int, char>> res;
    bool right = true;
    while (y) {
        res.emplace_back(x / y, right ? 'R' : 'L');
        x %= y;
        std::swap(x, y);
        right ^= 1;
    }
    --res.back().first;
    return res;
}