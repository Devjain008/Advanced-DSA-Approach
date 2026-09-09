#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    string text, pattern;
    cin >> text >> pattern;

    vector<int> z(m, 0);

    string temp = text + "$" + pattern;
    int m = temp.size();

    int l = 0;
    int r = 0;

    for(int i = 1; i < m; i++) {
      if(i <= r) {
        z[i] = min(r - i + 1, z[i - l]);
      }
      while(i + z[i] < m && temp[z[i]] == temp[i+z[i]]) {
        z[i]++;
      }
      if(i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
      }
    }
    
}