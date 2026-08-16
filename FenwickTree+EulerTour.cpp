#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> tin, tout;
vector<long long> value;
vector<long long> base;
vector<long long> bit;

int timer = 0;
int n;

void dfs(int node, int parent)
{
    tin[node] = ++timer;
    base[timer] = value[node];

    for(int child : adj[node])
    {
        if(child == parent)
            continue;

        dfs(child, node);
    }

    tout[node] = timer;
}

void update(int index, long long value)
{
    while(index <= n)
    {
        bit[index] += value;
        index += index & -index;
    }
}

long long query(int index)
{
    long long sum = 0;

    while(index > 0)
    {
        sum += bit[index];
        index -= index & -index;
    }

    return sum;
}

long long subtreeQuery(int node)
{
    return query(tout[node]) - query(tin[node] - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    adj.resize(n + 1);
    value.resize(n + 1);
    tin.resize(n + 1);
    tout.resize(n + 1);
    base.resize(n + 1);
    bit.resize(n + 1);

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
        update(i, base[i]);

    int q;
    cin >> q;

    while(q--)
    {
        int type;
        cin >> type;

        if(type == 1)
        {
            int node;
            long long newValue;

            cin >> node >> newValue;

            long long difference = newValue - value[node];

            value[node] = newValue;

            update(tin[node], difference);
        }
        else
        {
            int node;
            cin >> node;

            cout << subtreeQuery(node) << '\n';
        }
    }

    return 0;
}