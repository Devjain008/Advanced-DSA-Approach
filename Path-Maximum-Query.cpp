#include<bits/stdc++.h>
using namespace std;

vector<int>a;
vector<vector<int>>adj;
vector<int>parent, sub, depth;
vector<int>heavy, head, pos, base;
vector<int>seg;
int curr = -1;
int n, q;

void dfs(int node, int par) {
    parent[node] = par;
    sub[node] = 1;
    heavy[node] = -1;
    
    int mx = 0;
    
    for(int child : adj[node]) {
        if(child == par) continue;
        
        depth[child] = 1 + depth[node];
        dfs(child, node);
        sub[node] += sub[child];
        
        if(mx < sub[child]) {
            mx = sub[child];
            heavy[node] = child;
        }
    }
}

void decompose(int node, int h) {
    curr++;
    head[node] = h;
    pos[node] = curr;
    base[curr] = a[node];
    
    if(heavy[node] != -1) {
        decompose(heavy[node], h);
    }
    
    for(int child : adj[node]) {
        if(child == parent[node] || child == heavy[node]) continue;
        
        decompose(child, child);
    }
}

void build(int idx, int low, int high) {
    if(low == high) {
        seg[idx] = base[low];
        return;
    }
    
    int mid = low + (high - low)/2;
    
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);
    
    seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]);
}
void update(int idx, int low, int high, int i, int val) {
    if(low == high) {
        seg[idx] = val;
        return;
    }
    
    int mid = low + (high - low)/2;
    
    if(i <= mid) update(2 * idx + 1, low, mid, i, val);
    else update(2 * idx + 2, mid + 1, high, i, val);
    
    seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]);
}
int query(int idx, int low, int high, int l, int h) {
    if(low > h || high < l) return INT_MIN;
    if(low >= l && high <= h) return seg[idx];
    
    int mid = low + (high - low)/2;
    
    int left = query(2 * idx + 1, low, mid, l, h);
    int right = query(2 * idx + 2, mid + 1, high, l, h);
    
    return max(left, right);
}
int get(int u, int v) {
    
    int ans = 0;
    while(head[u] != head[v]) {
        if(depth[head[u]] < depth[head[v]]) {
            swap(u, v);
        }
        ans = max(ans, query(0, 0, n - 1, pos[head[u]], pos[u]));
        u = parent[head[u]];
    }
    if(depth[u] > depth[v]) {
        swap(u, v);
    }
    ans = max(ans, query(0, 0, n - 1, pos[u], pos[v]));
    return ans;
    
}


int main() {
    
    cin>>n>>q;
    
    a.resize(n + 1);
    adj.resize(n + 1);
    parent.resize(n + 1);
    sub.resize(n + 1);
    depth.resize(n + 1);
    heavy.resize(n + 1);
    head.resize(n + 1);
    pos.resize(n + 1);
    base.resize(n + 1);
    seg.resize(4 * n + 7);
    
    for(int i = 1; i <= n; i++) {
        cin>>a[i];
    }
    
    for(int i = 1; i<n; i++) {
        int u, v;
        cin>>u>>v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[1] = 0;
    dfs(1, 0);
    decompose(1, 1);
    
    build(0, 0, n - 1);
    
    while(q--) {
        int type, l, r;
        cin>>type>>l>>r;
        if(type == 1) {
            update(0, 0, n - 1, pos[l], r);
        }
        else {
            cout<<get(l, r)<<"\n";
        }
    }
    
}