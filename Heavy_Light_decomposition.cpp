#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
vector<int> value(MAXN);

vector<int> parent(MAXN, -1);
vector<int> depth(MAXN, 0);
vector<vector<int>> adj(MAXN);
vector<int> heavy(MAXN);
vector<int> sub(MAXN);
vector<int> head(MAXN);
vector<int> pos(MAXN);
vector<int> base(MAXN);

void dfs(int node, int par)
{
  parent[node] = par;
  sub[node] = 1;
  heavy[node] = -1;
  int mx = 0;

  for (int child : adj[node])
  {
    if (child == par)
      continue;
    depth[child] = depth[node] + 1;
    dfs(child, node);
    sub[node] += sub[child];

    if (sub[child] > mx)
    {
      mx = sub[child];
      heavy[node] = child;
    }
  }
}

int curPos = 0;
void decompose(int node, int h)
{
  head[node] = h;
  pos[node] = ++curPos;
  base[curPos] = value[node];

  if (heavy[node] != -1)
  {
    decompose(heavy[node], h);
  }

  for (int child : adj[node])
  {
    if (child == parent[node] || child == heavy[node])
      continue;

    decompose(child, child);
  }
}

vector<int> segTree(4 * MAXN, 0);
void build(int idx, int l, int r)
{
  if (l == r)
  {
    segTree[idx] = base[l];
    return;
  }

  int mid = (l + r) / 2;
  build(2 * idx, l, mid);
  build(2 * idx + 1, mid + 1, r);
  segTree[idx] = segTree[2 * idx] + segTree[2 * idx + 1];
}

void update(int idx, int l, int r, int p, int val)
{
  if (l == r)
  {
    segTree[idx] = val;
    return;
  }

  int mid = (l + r) / 2;
  if (p <= mid)
    update(2 * idx, l, mid, p, val);
  else
    update(2 * idx + 1, mid + 1, r, p, val);

  segTree[idx] = segTree[2 * idx] + segTree[2 * idx + 1];
}

int query(int idx, int l, int r, int ql, int qr)
{
  if (ql > r || qr < l)
    return 0;

  if (ql <= l && r <= qr)
    return segTree[idx];

  int mid = (l + r) / 2;
  return query(2 * idx, l, mid, ql, qr) +
         query(2 * idx + 1, mid + 1, r, ql, qr);
}

long long queryPath(int u, int v) {
  long long ans = 0;

  while (head[u] != head[v]) {
    if (depth[head[u]] < depth[head[v]])
      swap(u, v);

    ans += query(1, 1, curPos, pos[head[u]], pos[u]);
    u = parent[head[u]];
  }
  if (depth[u] < depth[v])
    swap(u, v);

  // u is now the deeper node on the shared chain, so pos[v] <= pos[u]
  ans += query(1, 1, curPos, pos[v], pos[u]);
  return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // Node values
    for (int i = 1; i <= n; i++)
        cin >> value[i];

    // Tree Input
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // First DFS
    depth[1] = 0;
    dfs(1, -1);

    // Second DFS (HLD Decomposition)
    curPos = 0;
    decompose(1, 1);

    // Build Segment Tree on Base Array
    build(1, 1, n);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            // Point Update
            int node, val;
            cin >> node >> val;

            update(1, 1, n, pos[node], val);
        }
        else
        {
            // Path Query
            int u, v;
            cin >> u >> v;

            cout << queryPath(u, v) << "\n";
        }
    }

    return 0;
}