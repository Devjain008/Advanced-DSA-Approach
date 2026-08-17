#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<long long> dist;

void dfs(int node, int parent)
{
    for(auto& [child, weight] : adj[node])
    {
        if(child == parent)
            continue;

        dist[child] = dist[node] + weight;

        dfs(child, node);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n + 1);
    dist.resize(n + 1, 0);

    for(int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dist[1] = 0;

    dfs(1, 0);

    for(int i = 1; i <= n; i++)
        cout << dist[i] << " ";

    return 0;
}