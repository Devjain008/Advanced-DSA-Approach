#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];

void dfs(int node, int parent)
{
    // Store immediate parent
    up[node][0] = parent;

    for (int j = 1; j < LOG; j++)
    {
        if (up[node][j - 1] != -1)
            up[node][j] = up[up[node][j - 1]][j - 1];
        else
            up[node][j] = -1;
    }

    for (int child : adj[node])
    {
        if (child == parent)
            continue;

        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

// Return kth ancestor
int kthAncestor(int node, int k)
{
    for (int j = 0; j < LOG; j++)
    {
        if (k & (1 << j))
        {
            node = up[node][j];

            if (node == -1)
                return -1;
        }
    }

    return node;
}

// Lowest Common Ancestor
int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (diff & (1 << j))
            u = up[u][j];
    }

    if (u == v)
        return u;

    // Lift both nodes together
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

// Distance between two nodes
int distanceNode(int u, int v)
{
    int ancestor = lca(u, v);

    return depth[u] + depth[v] - 2 * depth[ancestor];
}

int main()
{
    int n;
    cin >> n;

    // Input edges
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(up, -1, sizeof(up));

    depth[1] = 0;

    // Assume root = 1
    dfs(1, -1);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int node, k;
            cin >> node >> k;

            cout << kthAncestor(node, k) << endl;
        }
        else if (type == 2)
        {
            int u, v;
            cin >> u >> v;

            cout << lca(u, v) << endl;
        }
        else if (type == 3)
        {
            int u, v;
            cin >> u >> v;

            cout << distanceNode(u, v) << endl;
        }
    }

    return 0;
}