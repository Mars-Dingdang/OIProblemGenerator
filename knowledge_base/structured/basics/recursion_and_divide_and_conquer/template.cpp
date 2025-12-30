// General recursion template
int func(parameters) {
    if (base_case_condition) return base_case_value;
    // Process current state if needed
    return func(reduced_parameters); // Recursive call
}

// Divide and conquer template (e.g., merge sort)
void merge_sort(vector<int>& a, int l, int r) {
    if (l >= r) return; // Base case: single element
    int mid = l + (r - l) / 2;
    merge_sort(a, l, mid);      // Divide left
    merge_sort(a, mid + 1, r);  // Divide right
    merge(a, l, mid, r);        // Conquer/merge
}

// Helper merge function (example)
void merge(vector<int>& a, int l, int mid, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (int idx = 0; idx < k; ++idx) a[l + idx] = temp[idx];
}