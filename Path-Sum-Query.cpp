#include<bits/stdc++.h>
using namespace std;

vector<long long>a;
vector<vector<int>>adj;

vector<int>parent, sub, depth, heavy;
vector<int>head, pos;
vector<long long>base, seg;

int curr = 0;

void dfs(int node, int par) {
    parent[node] = par;
    sub[node] = 1;
    heavy[node] = -1;

    int mx = 0;

    for(int child : adj[node]) {
        if(child == par) continue;

        depth[child] = depth[node] + 1;

        dfs(child, node);

        sub[node] += sub[child];

        if(sub[child] > mx) {
            mx = sub[child];
            heavy[node] = child;
        }
    }
}

void decompose(int node, int h) {
    head[node] = h;
    pos[node] = curr;
    base[curr] = a[node];
    curr++;

    if(heavy[node] != -1) {
        decompose(heavy[node], h);
    }

    for(int child : adj[node]) {
        if(child == parent[node] || child == heavy[node])
            continue;

        decompose(child, child);
    }
}

void build(int idx, int low, int high) {
    if(low == high) {
        seg[idx] = base[low];
        return;
    }

    int mid = low + (high - low) / 2;

    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);

    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void update(int idx, int low, int high, int i, long long val) {
    if(low == high) {
        seg[idx] = val;
        return;
    }

    int mid = low + (high - low) / 2;

    if(i <= mid) {
        update(2 * idx + 1, low, mid, i, val);
    }
    else {
        update(2 * idx + 2, mid + 1, high, i, val);
    }

    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

long long query(int idx, int low, int high, int l, int r) {
    if(r < low || high < l)
        return 0;

    if(l <= low && high <= r)
        return seg[idx];

    int mid = low + (high - low) / 2;

    long long left = query(2 * idx + 1,low,mid,l,r);

    long long right = query(2 * idx + 2,mid + 1,high,l,r);

    return left + right;
}

long long queryPath(int u, int v, int n) {
    long long ans = 0;

    while(head[u] != head[v]) {

        if(depth[head[u]] < depth[head[v]]) {
            swap(u, v);
        }

        ans += query(0,0,n - 1,pos[head[u]],pos[u]);

        u = parent[head[u]];
    }

    if(depth[u] > depth[v]) {
        swap(u, v);
    }

    ans += query(0,0,n - 1,pos[u],pos[v]);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    a.resize(n + 1);
    adj.resize(n + 1);

    parent.resize(n + 1);
    sub.resize(n + 1);
    depth.resize(n + 1);
    heavy.resize(n + 1);

    head.resize(n + 1);
    pos.resize(n + 1);

    base.resize(n);
    seg.resize(4 * n);

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[1] = 0;

    dfs(1, 0);

    decompose(1, 1);

    build(0, 0, n - 1);

    while(q--) {
        int type;
        int u;
        long long v;

        cin >> type >> u >> v;

        if(type == 1) {
            update(0,0,n - 1,pos[u],v);
        }
        else {
            cout << queryPath(u, (int)v, n) << '\n';
        }
    }

    return 0;
}