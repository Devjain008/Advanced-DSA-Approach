#include<bits/stdc++.h>
using namespace std;  

int n;
vector<vector<int>>cost;
vector<vector<long long>>dp;

long long f(int mask, int last) {
  if(mask == (1 << n) - 1) {
    return cost[last][0];
  }
  if(dp[mask][last] != -1) {
    return dp[mask][last];
  }

  long long ans = LLONG_MAX;

  for(int i = 0; i < n; i++) {
    if(mask & (1<<i)) continue;

    int newmask = mask | (1<<i);
    ans = min(ans, cost[last][i] + f(newmask, i));
  }
  return dp[mask][last] = ans;
}

int main() {
  cin>>n;
  cost.resize(n, vector<int>(n));
  dp.resize(1<<n, vector<long long>(n, -1));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin>>cost[i][j];
    }
  }

  cout<<f(1, 0)<<endl;
}