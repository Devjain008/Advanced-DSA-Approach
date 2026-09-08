#include<bits/stdc++.h>
using namespace std;

//Initialize the Fenwick Tree with size n
class FenwickTree {
    int n;
    vector<int> bit;

public:
    FenwickTree(int n) {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void update(int idx, int val) {
        while(idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int ans = 0;

        while(idx > 0) {
            ans += bit[idx];
            idx -= idx & -idx;
        }

        return ans;
    }

    int queryRange(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
  int n;
  cin >> n;

  // Read the input array
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  // Create a Fenwick Tree of size n
  FenwickTree ft(n);

  for(int i = 0; i < n; i++) {
    ft.update(i + 1, a[i]); // Update the Fenwick Tree with the initial values
  }

  int q;
  cin >> q;

  while(q--) {
    int type;
    cin >> type;
    
    if(type == 1) {
      int idx, val;
      cin >> idx >> val;
      // Update the value at index idx by val in the Fenwick Tree
      ft.update(idx, val);
    } else if(type == 2) {
      int l, r;
      cin >> l >> r;

      // Query the sum of elements from index l to r in the Fenwick Tree
      cout << ft.queryRange(l, r) << endl;
    }
  }


}