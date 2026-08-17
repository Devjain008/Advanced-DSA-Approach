#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> depth;
vector<vector<int>> dp;

void dfs(int node, int parent)
{
    dp[node][0] = 0;
    dp[node][1] = 1;

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        dfs(child, node);
        dp[node][0] += max(dp[node][0], dp[node][1]);
        dp[node][1] += dp[child][0];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n + 1);
    depth.resize(n + 1);
    dp.resize(n + 1, vector<int>(2));

    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    cout << max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}