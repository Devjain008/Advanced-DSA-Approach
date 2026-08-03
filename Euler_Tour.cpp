#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];

int tin[MAXN];
int tout[MAXN];
int depth[MAXN];
int euler[MAXN];

int timer = 0;

void dfs(int node, int parent)
{
    // Entry Time
    tin[node] = ++timer;

    // Flatten Tree
    euler[timer] = node;

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        depth[child] = depth[node] + 1;

        dfs(child, node);
    }

    // Exit Time
    tout[node] = timer;
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

    depth[1] = 0;

    dfs(1, -1);

    cout << "Node\tTin\tTout\tDepth\n";

    for(int i = 1; i <= n; i++)
    {
        cout << i << "\t"
             << tin[i] << "\t"
             << tout[i] << "\t"
             << depth[i] << "\n";
    }

    cout << "\nEuler Array\n";

    for(int i = 1; i <= n; i++)
        cout << euler[i] << " ";

    cout << "\n";
}