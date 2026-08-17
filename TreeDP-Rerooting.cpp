#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> sub;
vector<long long> dp;
vector<long long> ans;

int n;

void dfs1(int node, int parent)
{
    sub[node] = 1;
    dp[node] = 0;

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        dfs1(child, node);

        sub[node] += sub[child];
        dp[node] += dp[child] + sub[child];
    }
}

void dfs2(int node, int parent)
{
    ans[node] = dp[node];

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        dp[child] = dp[node] + n - 2LL * sub[child];

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
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1, 0);

    dfs2(1, 0);

    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";

    return 0;
}