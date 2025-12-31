int n;
char s[MAXN * 2 + 5];
int R[MAXN * 2 + 5];

void manacher() {
    int p = 0, mx = 0;
    for (int i = 1; i <= n; ++i) {
        if (mx > i) {
            R[i] = std::min(R[2 * p - i], mx - i);
        } else {
            R[i] = 1;
        }
        while (s[i + R[i]] == s[i - R[i]]) {
            ++R[i];
        }
        if (i + R[i] > mx) {
            mx = i + R[i];
            p = i;
        }
    }
}

// Example preprocessing
void preprocess(const std::string& str) {
    s[0] = '$';
    s[1] = '#';
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        s[i * 2 + 2] = str[i];
        s[i * 2 + 3] = '#';
    }
    n = len * 2 + 2;
    s[n + 1] = '@';
    s[n + 2] = '\0';
}