#include <bits/stdc++.h>
using namespace std;

class SEG {
public:
    vector<int> seg, lazy;

    SEG(int n) {
        seg.resize(4 * n + 7);
        lazy.resize(4 * n + 7);
    }

    void push(int idx, int low, int high) {
        if(lazy[idx] == 0)
            return;

        seg[idx] += (high - low + 1) * lazy[idx];

        if(low != high) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }

        lazy[idx] = 0;
    }

    void update(int idx, int low, int high, int i, int val) {
        push(idx, low, high);

        if(low == high) {
            seg[idx] = val;
            return;
        }

        int mid = low + (high - low) / 2;

        if(i <= mid)
            update(2 * idx + 1, low, mid, i, val);
        else
            update(2 * idx + 2, mid + 1, high, i, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r) {
        push(idx, low, high);

        if(high < l || low > r)
            return 0;

        if(l <= low && high <= r)
            return seg[idx];

        int mid = low + (high - low) / 2;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return left + right;
    }

    void updateRange(int idx, int low, int high,
                     int l, int r, int val) {
        push(idx, low, high);

        if(high < l || low > r)
            return;

        if(l <= low && high <= r) {
            lazy[idx] += val;
            push(idx, low, high);
            return;
        }

        int mid = low + (high - low) / 2;

        updateRange(2 * idx + 1, low, mid, l, r, val);
        updateRange(2 * idx + 2, mid + 1, high, l, r, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    SEG seg(n);

    while(q--) {
        int type;
        cin >> type;

        if(type == 1) {
            int i, val;
            cin >> i >> val;

            seg.update(0, 0, n - 1, i, val);
        }
        else if(type == 2) {
            int l, r;
            cin >> l >> r;

            cout << seg.query(0, 0, n - 1, l, r) << '\n';
        }
        else {
            int l, r, val;
            cin >> l >> r >> val;

            seg.updateRange(0, 0, n - 1, l, r, val);
        }
    }

    return 0;
}