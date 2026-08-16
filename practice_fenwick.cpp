#include <bits/stdc++.h>
using namespace std;

class Fenwick
{
    int n;
    vector<long long> bit;

public:

    Fenwick(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void update(int idx, long long val)
    {
        while(idx <= n)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    long long query(int idx)
    {
        long long sum = 0;

        while(idx > 0)
        {
            sum += bit[idx];
            idx -= idx & -idx;
        }

        return sum;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> a[i];

    Fenwick fenwick(n);

    while(q--)
    {
        int l, r;
        cin >> l >> r;

        fenwick.update(l, 1);

        if(r + 1 <= n)
            fenwick.update(r + 1, -1);
    }

    vector<long long> cnt(n + 1);

    for(int i = 1; i <= n; i++)
        cnt[i] = fenwick.query(i);

    vector<pair<long long, int>> order;

    for(int i = 1; i <= n; i++)
        order.push_back({cnt[i], i});

    sort(order.rbegin(), order.rend());

    sort(a.begin() + 1, a.end(), greater<long long>());

    long long answer = 0;

    for(int i = 0; i < n; i++)
        answer += order[i].first * a[i + 1];

    cout << answer << '\n';

    return 0;
}