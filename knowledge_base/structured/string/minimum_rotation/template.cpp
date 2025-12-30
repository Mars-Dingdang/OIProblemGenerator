int minimum_rotation(const string &s) {
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n];
        char b = s[(j + k) % n];
        if (a == b) {
            ++k;
        } else {
            if (a > b) {
                i = i + k + 1;
            } else {
                j = j + k + 1;
            }
            if (i == j) ++i;
            k = 0;
        }
    }
    return min(i, j);
}