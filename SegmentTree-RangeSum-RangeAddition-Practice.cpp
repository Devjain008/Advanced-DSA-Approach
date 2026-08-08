#include <bits/stdc++.h>
using namespace std;

class SEG {
    vector<long long> seg;
    vector<long long> arr;
    vector<long long> lazy;
    public:
    
    SEG(int n, vector<long long>& nums) {
        seg.resize(4 * n + 7);
        lazy.resize(4 * n + 7, 0);
        arr = nums;
    }
    
    void build(int idx, int low, int high) {
        if(low == high) {
            seg[idx] = arr[low];
            return;
        }
        int mid = low + (high - low)/2;
        build(2 * idx + 1, low, mid);
        build(2 * idx + 2, mid + 1, high);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    void push(int idx, int low, int high) {
        if(lazy[idx] == 0) return;
        
        seg[idx] += (lazy[idx])*(high - low + 1);
        
        if(low != high) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    
    void updateRange(int idx, int low, int high, int l, int r, int val) {
        push(idx, low, high);
        
        if (high < l || low > r) return;

        if (l <= low && high <= r) {
            lazy[idx] += val;
            push(idx, low, high);
            return;
        }
        
        int mid = low + (high - low)/2;
        
        updateRange(2 * idx + 1, low, mid, l, r, val);
        updateRange(2 * idx + 2, mid + 1, high, l, r, val);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
        
    }
    
    void updatePoint(int idx, int low, int high, int i, int val) {
        push(idx, low, high);
        if(low == high) {
            seg[idx] = val;
            return;
        }
        int mid = low + (high - low)/2;
        
        if(mid >= i) {
            updatePoint(2 * idx + 1, low, mid, i, val);
        } else{
            updatePoint(2 * idx + 2, mid + 1, high, i, val);
        }
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    
    int query(int idx, int low, int high, int l, int r) {
        
        push(idx, low, high);
        
        if(low > r || high < l) return 0;
        if(low >= l && high <= r) return seg[idx];
        
        int mid = low + (high - low)/2;
        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);
        return  left + right;
    }
};
int main() {
    SEG* st;
    int n;
    cin>>n;
    vector<long long>arr(n);
    
    for(int i = 0; i<n; i++) cin>>arr[i];
    
    st = new SEG(n, arr);
    st->build(0, 0, n - 1);
    
    int q;
    cin>>q;
    
    while(q--) {
        int type;
        cin>>type;
        
        if(type == 1) {
            int idx, val;
            cin>>idx>>val;
            st->updatePoint(0, 0, n - 1, idx, val);
        }
        else if(type == 2) {
            int l, r, val;
            cin>>l>>r>>val;
            st->updateRange(0, 0, n - 1, l, r, val);
        }
        else{
            int l, r;
            cin>>l>>r;
            int ans = st->query(0, 0, n - 1, l, r);
            cout<<ans<<"\n";
        }
    }
    return 0;

}
