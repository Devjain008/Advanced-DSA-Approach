#include <bits/stdc++.h>
using namespace std;

bool isSafe(int i, int j, vector<vector<int>> &mat, vector<vector<int>> &vis)
{
  int n = mat.size();
  for (int i = 0; i < n; i++)
  {
    if (vis[0][i] == 1)
      return false;
    if (vis[i][0] == 1)
      return false;
  }
}

int f(int i, int j, vector<vector<int>> &mat, vector<vector<int>> &vis)
{
  int n = mat.size();
  if (i == n)
    return 0;

  long long ans = 0;

  for (int k = 0; k < n; k++)
  {
    if (isSafe(i, k, mat, vis))
    {
      ans += f(i + 1, k, mat, vis);
    }
  }

  return ans;
}

int main()
{
  int n;
  cin >> n;

  vector<vector<int>> mat(n, vector<int>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; i < n; j++)
    {
      cin >> mat[i][j];
    }
  }

  int ans = 1e9 + 7;

  for (int i = 0; i < n; i++)
  {
    vector<vector<int>> vis(n, vector<int>(n, 0));
    ans = min(ans, f(0, i, mat, vis));
  }

  cout << ans << "\n";
}