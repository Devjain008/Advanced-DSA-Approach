#include<bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin>>n;

  vector<vector<int>>cost(n, vector<int>(n));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin>>cost[i][j];
    }
  }

  int total = 1 << n;
  long long INF = 1e18;

  vector<long long>dp(total, INF);
  dp[0] = 0;

  for(int mask = 0; mask < total; mask++) {
    int cnt = __builtin_popcount(mask);

    if(cnt == n) {
      continue;
    }

    for(int i= 0; i<n; i++) {
      if(mask & (1<<i)) continue;

      int newmask = mask | (1<<i);

      dp[newmask] = min(dp[newmask], dp[mask] + cost[cnt][i]);
    }
  }
  cout<<dp[total-1]<<endl;
  
}