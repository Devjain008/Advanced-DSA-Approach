#include<bits/stdc++.h>
using namespace std;

int n, k;

int f(int idx, int rem, vector<int>& a, vector<vector<int>>& dp) {
  if(idx == a.size()) {
    return rem == 0 ? 1 : 0;
  }
  if(dp[idx][rem] != -1) {
    return dp[idx][rem];
  } 
  int notTake = f(idx + 1, rem, a, dp);
  int next = (rem + a[idx]) % k;
  int take = f(idx + 1, next, a, dp);

  return dp[idx][rem] = take + notTake;
}

int main() {
  cin>>n>>k;
  vector<int>a(n);
  for(int i = 0; i < n; i++) {
    cin>>a[i];
  }
  vector<vector<int>>dp(n, vector<int>(k, -1));
  cout<<f(0, 0, a, dp)<<endl;
}