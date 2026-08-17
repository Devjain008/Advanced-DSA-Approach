#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<long long> value;
vector<long long>dp;

void dfs(int node, int parent)
{
    dp[node] = value[node];

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        dfs(child, node);
        dp[node] += dp[child];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n + 1);
    value.resize(n + 1);
    dp.resize(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> value[i];

    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for(int i = 1; i <= n; i++)
        cout << dp[i] << " ";
    
    return 0;
}