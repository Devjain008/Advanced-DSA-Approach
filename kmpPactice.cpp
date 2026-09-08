#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin>>n>>m;

  string pattern, text;
  cin>>pattern>>text;

  int i = 1;
  int len = 0;

  vector<int> lps(m, 0);

  while(i < m) {
    if(pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if(len != 0) {
        len = lps[len -1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  i = 0;
  int j = 0;

  while(i < n) {
    if(text[i] == pattern[j]) {
      i++;
      j++;

      if(j == m) {
        cout<<i - j<<"\n";

        j = lps[j - 1];
      }
    } else {
      if(j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
}