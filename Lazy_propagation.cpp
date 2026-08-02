#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<long long> seg, lazy;

public:
    SegmentTree(int n) {
        seg.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int ind, int low, int high, vector<int> &arr) {

        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;

        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void update(int ind, int low, int high, int l, int r, int val) {

        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * 1LL * lazy[ind];

            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }

            lazy[ind] = 0;
        }

        if (high < l || low > r)
            return;

        if (low >= l && high <= r) {

            seg[ind] += (high - low + 1) * 1LL * val;

            if (low != high) {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }

            return;
        }

        int mid = (low + high) / 2;

        update(2 * ind + 1, low, mid, l, r, val);
        update(2 * ind + 2, mid + 1, high, l, r, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    long long query(int ind, int low, int high, int l, int r) {

        if (lazy[ind] != 0) {

            seg[ind] += (high - low + 1) * 1LL * lazy[ind];

            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }

            lazy[ind] = 0;
        }

        if (high < l || low > r)
            return 0;

        if (low >= l && high <= r)
            return seg[ind];

        int mid = (low + high) / 2;

        return query(2 * ind + 1, low, mid, l, r) +
               query(2 * ind + 2, mid + 1, high, l, r);
    }
};


int main() {
    cout << "Hello World";
    return 0;
}