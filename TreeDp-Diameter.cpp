#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> dp;

int diameter = 0;

void dfs(int node, int parent)
{
    int best1 = 0;
    int best2 = 0;

    for(auto& [child, weight] : adj[node])
    {
        if(child == parent)
            continue;

        dfs(child, node);

        int path = dp[child] + weight;

        if(path > best1)
        {
            best2 = best1;
            best1 = path;
        }
        else if(path > best2)
        {
            best2 = path;
        }
    }

    dp[node] = best1;

    diameter = max(diameter, best1 + best2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n + 1);
    dp.resize(n + 1, 0);

    for(int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs(1, 0);

    cout << diameter << '\n';

    return 0;
}