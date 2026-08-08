#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<long long> tree, lazy;
    int n;

public:
    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1, arr);
    }

    void build(int node, int left, int right, const vector<long long>& arr) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;

        build(2 * node + 1, left, mid, arr);
        build(2 * node + 2, mid + 1, right, arr);

        tree[node] = min(tree[2 * node + 1],
                         tree[2 * node + 2]);
    }

    void push(int node) {
        if (lazy[node] == 0)
            return;

        tree[node] += lazy[node];

        if (node * 2 + 1 < 4 * n) {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }

        lazy[node] = 0;
    }

    void update(int node, int left, int right,
                int ql, int qr, long long value) {

        push(node);

        if (right < ql || left > qr)
            return;

        if (ql <= left && right <= qr) {
            lazy[node] += value;
            push(node);
            return;
        }

        int mid = left + (right - left) / 2;

        update(2 * node + 1, left, mid, ql, qr, value);
        update(2 * node + 2, mid + 1, right, ql, qr, value);

        tree[node] = min(tree[2 * node + 1],
                         tree[2 * node + 2]);
    }

    long long query(int node, int left, int right,
                    int ql, int qr) {

        push(node);

        if (right < ql || left > qr)
            return LLONG_MAX;

        if (ql <= left && right <= qr)
            return tree[node];

        int mid = left + (right - left) / 2;

        return min(
            query(2 * node + 1, left, mid, ql, qr),
            query(2 * node + 2, mid + 1, right, ql, qr)
        );
    }

    void update(int left, int right, long long value) {
        update(0, 0, n - 1, left, right, value);
    }

    long long query(int left, int right) {
        return query(0, 0, n - 1, left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> arr(n);

    for (auto& x : arr)
        cin >> x;

    SegmentTree st(arr);

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            long long value;
            cin >> l >> r >> value;

            st.update(l, r, value);
        }
        else {
            int l, r;
            cin >> l >> r;

            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}