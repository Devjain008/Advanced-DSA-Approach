#include<bits/stdc++.h>
using namespace std;

class SEG {
  vector<int>seg, lazy;
  public:
  SEG(int n) {
    seg.resize(4 * n + 7);
    lazy.resize(4 * n + 7, 0);
  }
  void build(int idx, int low, int high, vector<int>& nums) {
    if(low == high) {
      seg[idx] = nums[low];
      return ;
    }
    int mid = low + (high - low) / 2;
    build(2 * idx + 1, low, mid, nums);
    build(2 * idx + 2, mid + 1, high, nums);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
  }
  void push(int idx, int low, int high) {
  if(lazy[idx] == 0) return;
  seg[idx] += (high - low + 1) * lazy[idx];

  if(low != high) {
    lazy[2 * idx + 1] += lazy[idx];
    lazy[2 * idx + 2] += lazy[idx];
  }
  lazy[idx] = 0;
  }
  void update(int idx, int low, int high, int i, int val) {
    push(idx, low, high);
    if(low == high) {
      seg[idx] = val;
      return ;
    }
    int mid = low + (high - low) / 2;
    if(i <= mid) update(2 * idx + 1, low, mid, i, val);
    else update(2 * idx + 2, mid + 1, high, i, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
  }
  void updateRange(int idx, int low, int high, int l, int h, int val) {
    push(idx, low, high);
    if(low > h || high < l) return;
    if(low >= l && high <= h){
      lazy[idx] += val;
      seg[idx] += (high - low + 1) * val;
      
      return;
    } 
    int mid = low + (high - low) / 2;
    updateRange(2 * idx + 1, low, mid, l, h, val);
    updateRange(2 * idx + 2, mid + 1, high, l, h, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
  }
  int query(int idx, int low, int high, int l, int h) {
     push(idx, low, high);
    if(low > h || high < l) return 0;
    if(low >= l && high <= h) return seg[idx];

    int mid = low + (high - low) / 2;
    int left = query(2 * idx + 1, low, mid, l, h);
    int right = query(2 * idx + 2, mid + 1, high, l, h);
    return left + right;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin>>n;

  vector<int>a(n);
  
  for(int i = 0; i<n; i++) cin>>a[i];

  
  SEG *st = new SEG(n);
  st->build(0, 0, n - 1, a);

  int q;
  cin>>q;
  while(q--) {
    int type;
    cin>>type;

    if(type == 1) {
      int i, val;
      cin>>i>>val;
      st->update(0, 0, n - 1, i, val);
    }
    else if(type == 2) {
      int l, r, val;
      cin>>l>>r>>val;
      st->updateRange(0, 0, n - 1, l, r, val);
    }
    else{
      int l, r;
      cin>>l>>r;
      cout<<st->query(0, 0, n - 1, l, r)<<"\n";
    }
  }
}