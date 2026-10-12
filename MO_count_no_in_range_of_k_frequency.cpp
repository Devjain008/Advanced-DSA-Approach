
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int q, k;
    cin >> q >> k;

    vector<Query> queries(q);

    for(int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    // Coordinate compression
    vector<int> compressed = a;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()),
                     compressed.end());

    for(int &x : a) {
        x = lower_bound(compressed.begin(), compressed.end(), x)
            - compressed.begin();
    }

    int blockSize = max(1, (int)sqrt(n));

    sort(queries.begin(), queries.end(),
         [blockSize](const Query &a, const Query &b) {
        int blockA = a.l / blockSize;
        int blockB = b.l / blockSize;

        if(blockA != blockB) {
            return blockA < blockB;
        }

        return (blockA & 1) ? a.r > b.r : a.r < b.r;
    });

    vector<int> freq(compressed.size(), 0);
    vector<int> ans(q);

    int curL = 0, curR = -1;
    int distinctAtLeastK = 0;

    auto add = [&](int idx) {
        int x = a[idx];

        if(freq[x] == k - 1) {
            distinctAtLeastK++;
        }

        freq[x]++;
    };

    auto remove = [&](int idx) {
        int x = a[idx];

        if(freq[x] == k) {
            distinctAtLeastK--;
        }

        freq[x]--;
    };

    for(auto &query : queries) {
        int l = query.l;
        int r = query.r;

        while(curL > l) add(--curL);
        while(curR < r) add(++curR);
        while(curL < l) remove(curL++);
        while(curR > r) remove(curR--);

        ans[query.idx] = distinctAtLeastK;
    }

    for(int x : ans) {
        cout << x << '\n';
    }

    return 0;
}
