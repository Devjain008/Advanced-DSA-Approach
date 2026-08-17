#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> sub;
vector<long long> dp;
vector<long long> ans;

int n;

void dfs1(int node, int parent)
{
    sub[node] = 1;
    dp[node] = 0;

    for(auto [child, weight] : adj[node])
    {
        if(child == parent)
            continue;

        dfs1(child, node);

        sub[node] += sub[child];

        dp[node] += dp[child] + 1LL * sub[child] * weight;
    }
}

void dfs2(int node, int parent)
{
    for(auto [child, weight] : adj[node])
    {
        if(child == parent)
            continue;

        ans[child] = ans[node]
                   + 1LL * (n - 2 * sub[child]) * weight;

        dfs2(child, node);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    adj.resize(n + 1);
    sub.resize(n + 1);
    dp.resize(n + 1);
    ans.resize(n + 1);

    for(int i = 0; i < n - 1; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs1(1, 0);

    ans[1] = dp[1];

    dfs2(1, 0);

    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";

    return 0;
}