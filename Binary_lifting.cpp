#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];

int up[MAXN][LOG];
int depth[MAXN];

void dfs(int node, int parent)
{
    up[node][0] = parent;

    // Binary Lifting Table
    for(int j = 1; j < LOG; j++)
    {
        if(up[node][j-1] == -1)
            up[node][j] = -1;
        else
            up[node][j] = up[ up[node][j-1] ][j-1];
    }

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

int kthAncestor(int node, int k)
{
    for(int j = 0; j < LOG; j++)
    {
        if(k & (1 << j))
        {
            node = up[node][j];

            if(node == -1)
                return -1;
        }
    }

    return node;
}

int lca(int u, int v)
{
    // Step 1 : Bring both nodes to same depth
    if(depth[u] < depth[v])
        swap(u, v);

    u = kthAncestor(u, depth[u] - depth[v]);

    // If one node is ancestor of another
    if(u == v)
        return u;

    // Step 2 : Lift both together
    for(int j = LOG - 1; j >= 0; j--)
    {
        if(up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }

    // Parent is LCA
    return up[u][0];
}

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(up, -1, sizeof(up));

    depth[1] = 0;

    dfs(1, -1);

    int q;
    cin >> q;

    while(q--)
    {
        int u, v;
        cin >> u >> v;

        cout << lca(u, v) << "\n";
    }
}