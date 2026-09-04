#include<bits/stdc++.h>
using namespace std;

class SEG {
    vector<int> seg, lazy;

public:
    SEG(int n) {
        seg.resize(4 * n + 7);
        lazy.resize(4 * n + 7, INT_MIN);
    }

    void build(int idx, int low, int high, vector<int>& nums) {
        if(low == high) {
            seg[idx] = nums[low];
            return;
        }

        int mid = low + (high - low) / 2;
        int len = 2 * idx;

        build(len + 1, low, mid, nums);
        build(len + 2, mid + 1, high, nums);

        seg[idx] = max(seg[len + 1], seg[len + 2]);
    }

    void push(int idx, int low, int high) {
        if(lazy[idx] == INT_MIN) return;

        seg[idx] = lazy[idx];

        if(low != high) {
            int len = 2 * idx;

            lazy[len + 1] = lazy[idx];
            lazy[len + 2] = lazy[idx];
        }

        lazy[idx] = INT_MIN;
    }

    void update(int idx, int low, int high, int i, int val) {
        push(idx, low, high);

        if(low == high) {
            seg[idx] = val;
            return;
        }

        int mid = low + (high - low) / 2;
        int len = 2 * idx;

        if(i <= mid)
            update(len + 1, low, mid, i, val);
        else
            update(len + 2, mid + 1, high, i, val);

        seg[idx] = max(seg[len + 1], seg[len + 2]);
    }

    void updateRange(int idx, int low, int high, int l, int h, int val) {
        if(low > h || high < l)
            return;

        if(low >= l && high <= h) {
            lazy[idx] = val;
            push(idx, low, high);
            return;
        }

        push(idx, low, high);

        int mid = low + (high - low) / 2;
        int len = 2 * idx;

        updateRange(len + 1, low, mid, l, h, val);
        updateRange(len + 2, mid + 1, high, l, h, val);

        seg[idx] = max(seg[len + 1], seg[len + 2]);
    }

    int query(int idx, int low, int high, int l, int h) {
        if(low > h || high < l)
            return INT_MIN;

        push(idx, low, high);

        if(low >= l && high <= h)
            return seg[idx];

        int mid = low + (high - low) / 2;
        int len = 2 * idx;

        int left = query(len + 1, low, mid, l, h);
        int right = query(len + 2, mid + 1, high, l, h);

        return max(left, right);
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    int q;
    cin >> q;

    vector<int> ans;

    SEG seg(n);

    seg.build(0, 0, n - 1, nums);

    while(q--) {
        int type;
        cin >> type;

        if(type == 1) {
            int i, val;
            cin >> i >> val;

            seg.update(0, 0, n - 1, i, val);
        }
        else if(type == 2) {
            int l, h, val;
            cin >> l >> h >> val;

            seg.updateRange(0, 0, n - 1, l, h, val);
        }
        else {
            int l, h;
            cin >> l >> h;

            ans.push_back(seg.query(0, 0, n - 1, l, h));
        }
    }

    for(int x : ans)
        cout << x << " ";

    return 0;
}