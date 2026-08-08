#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 200005;
const int LOG = 20;

int n, q;

vector<vector<int>> adj(MAXN);
vector<ll> value(MAXN);

int up[MAXN][LOG];

int parentNode[MAXN];
int depth[MAXN];
int subtreeSize[MAXN];
int heavy[MAXN];

// Euler Tour
int tin[MAXN];
int tout[MAXN];
int timer = 0;

vector<ll> eulerBase(MAXN);

// HLD
int head[MAXN];
int pos[MAXN];
int currentPos = 0;

vector<ll> hldBase(MAXN);

// ============================================================
// Segment Tree
// ============================================================

class SegmentTree
{
    vector<ll> tree;

public:

    SegmentTree(int n)
    {
        tree.resize(4 * n + 5);
    }

    void build(int node, int left, int right, const vector<ll>& base)
    {
        if (left == right)
        {
            tree[node] = base[left];
            return;
        }

        int mid = (left + right) / 2;

        build(2 * node, left, mid, base);
        build(2 * node + 1, mid + 1, right, base);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void build(const vector<ll>& base, int n)
    {
        build(1, 1, n, base);
    }

    void update(int node, int left, int right, int index, ll value)
    {
        if (left == right)
        {
            tree[node] = value;
            return;
        }

        int mid = (left + right) / 2;

        if (index <= mid)
            update(2 * node, left, mid, index, value);
        else
            update(2 * node + 1, mid + 1, right, index, value);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int index, ll value, int n)
    {
        update(1, 1, n, index, value);
    }

    ll query(int node, int left, int right, int ql, int qr)
    {
        if (qr < left || right < ql)
            return 0;

        if (ql <= left && right <= qr)
            return tree[node];

        int mid = (left + right) / 2;

        return query(2 * node, left, mid, ql, qr)
             + query(2 * node + 1, mid + 1, right, ql, qr);
    }

    ll query(int left, int right, int n)
    {
        return query(1, 1, n, left, right);
    }
};


// ============================================================
// DFS
// ============================================================

void dfs(int node, int parent)
{
    parentNode[node] = parent;
    depth[node] = (parent == 0 ? 0 : depth[parent] + 1);

    subtreeSize[node] = 1;
    heavy[node] = -1;

    // Binary Lifting
    up[node][0] = parent;

    for (int j = 1; j < LOG; j++)
    {
        up[node][j] = up[up[node][j - 1]][j - 1];
    }

    // Euler Tour
    tin[node] = ++timer;
    eulerBase[timer] = value[node];

    int largestSubtree = 0;

    for (int child : adj[node])
    {
        if (child == parent)
            continue;

        dfs(child, node);

        subtreeSize[node] += subtreeSize[child];

        if (subtreeSize[child] > largestSubtree)
        {
            largestSubtree = subtreeSize[child];
            heavy[node] = child;
        }
    }

    tout[node] = timer;
}


// ============================================================
// HLD Decomposition
// ============================================================

void decompose(int node, int chainHead)
{
    head[node] = chainHead;
    pos[node] = ++currentPos;
    hldBase[currentPos] = value[node];

    // Continue Heavy Chain
    if (heavy[node] != -1)
        decompose(heavy[node], chainHead);

    // Start Light Chains
    for (int child : adj[node])
    {
        if (child == parentNode[node] || child == heavy[node])
            continue;

        decompose(child, child);
    }
}


// ============================================================
// K-th Ancestor
// ============================================================

int kthAncestor(int node, int k)
{
    for (int j = 0; j < LOG; j++)
    {
        if (k & (1 << j))
            node = up[node][j];

        if (node == 0)
            return -1;
    }

    return node;
}


// ============================================================
// Subtree Query
// ============================================================

ll querySubtree(int node, SegmentTree& eulerTree)
{
    return eulerTree.query(tin[node], tout[node], n);
}


// ============================================================
// HLD Path Query
// ============================================================

ll queryPath(int u, int v, SegmentTree& hldTree)
{
    ll answer = 0;

    while (head[u] != head[v])
    {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);

        answer += hldTree.query(pos[head[u]], pos[u], n);

        u = parentNode[head[u]];
    }

    if (depth[u] > depth[v])
        swap(u, v);

    answer += hldTree.query(pos[u], pos[v], n);

    return answer;
}


// ============================================================
// Main
// ============================================================

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> value[i];

    // Tree Input
    for (int i = 2; i <= n; i++)
    {
        int parent;
        cin >> parent;

        adj[parent].push_back(i);
        adj[i].push_back(parent);
    }

    // 1. DFS: Binary Lifting + Euler + Heavy Child
    dfs(1, 0);

    // 2. HLD Decomposition
    decompose(1, 1);

    // 3. Segment Trees
    SegmentTree eulerTree(n);
    SegmentTree hldTree(n);

    eulerTree.build(eulerBase, n);
    hldTree.build(hldBase, n);

    // 4. Queries
    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int node, k;
            cin >> node >> k;

            cout << kthAncestor(node, k) << '\n';
        }
        else if (type == 2)
        {
            int node;
            cin >> node;

            cout << querySubtree(node, eulerTree) << '\n';
        }
        else if (type == 3)
        {
            int u, v;
            cin >> u >> v;

            cout << queryPath(u, v, hldTree) << '\n';
        }
        else if (type == 4)
        {
            int node;
            ll newValue;

            cin >> node >> newValue;

            value[node] = newValue;

            eulerTree.update(tin[node], newValue, n);
            hldTree.update(pos[node], newValue, n);
        }
    }

    return 0;
}