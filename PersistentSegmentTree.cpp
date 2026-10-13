
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class PersistentFrequencyTree {
    struct Node {
        int left, right, sum;

        Node(int l = 0, int r = 0, int s = 0)
            : left(l), right(r), sum(s) {}
    };

    vector<Node> tree;
    vector<int> root;
    vector<ll> values;
    int m;

    int update(int prev, int l, int r, int pos) {
        int cur = (int)tree.size();
        tree.push_back(tree[prev]);

        tree[cur].sum++;

        if (l == r) {
            return cur;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            tree[cur].left = update(
                tree[prev].left, l, mid, pos
            );
        } else {
            tree[cur].right = update(
                tree[prev].right, mid + 1, r, pos
            );
        }

        return cur;
    }

    // Count compressed ranks in [ql, qr].
    int query(int node, int l, int r, int ql, int qr) {
        if (node == 0 || qr < l || r < ql) {
            return 0;
        }

        if (ql <= l && r <= qr) {
            return tree[node].sum;
        }

        int mid = l + (r - l) / 2;

        return query(tree[node].left, l, mid, ql, qr)
             + query(tree[node].right, mid + 1, r, ql, qr);
    }

    // Difference of two prefix versions.
    int rangeCount(int u, int v, int l, int r,
                   int ql, int qr) {
        if (qr < l || r < ql) {
            return 0;
        }

        if (ql <= l && r <= qr) {
            return tree[v].sum - tree[u].sum;
        }

        int mid = l + (r - l) / 2;

        return rangeCount(
                   tree[u].left, tree[v].left,
                   l, mid, ql, qr
               )
             + rangeCount(
                   tree[u].right, tree[v].right,
                   mid + 1, r, ql, qr
               );
    }

public:
    PersistentFrequencyTree(vector<ll>& arr) {
        values = arr;
        sort(values.begin(), values.end());
        values.erase(
            unique(values.begin(), values.end()),
            values.end()
        );

        m = (int)values.size();

        // Node 0 is the empty tree.
        tree.push_back(Node());
        root.push_back(0);

        for (ll x : arr) {
            int pos = lower_bound(
                values.begin(), values.end(), x
            ) - values.begin();

            root.push_back(update(
                root.back(), 0, m - 1, pos
            ));
        }
    }

    int countInRange(int L, int R, ll A, ll B) {
        if (L < 0 || R + 1 >= (int)root.size()
            || L > R || A > B) {
            return 0;
        }

        // First compressed value >= A.
        int ql = lower_bound(
            values.begin(), values.end(), A
        ) - values.begin();

        // First compressed value > B.
        int qr = upper_bound(
            values.begin(), values.end(), B
        ) - values.begin() - 1;

        if (ql >= m || qr < 0 || ql > qr) {
            return 0;
        }

        return rangeCount(
            root[L], root[R + 1],
            0, m - 1, ql, qr
        );
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    PersistentFrequencyTree pst(arr);

    while (q--) {
        int L, R;
        ll A, B;
        cin >> L >> R >> A >> B;

        cout << pst.countInRange(L, R, A, B) << '\n';
    }

    return 0;
}
