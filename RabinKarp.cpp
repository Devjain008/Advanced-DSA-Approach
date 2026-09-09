#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;

const ll base1 = 31;
const ll base2 = 37;

vector<ll> power1, power2;
vector<ll> hash1, hash2;

pair<ll, ll> get_hash(string &s) {
    ll h1 = 0, h2 = 0;

    for(char c : s) {
        ll x = c - 'a' + 1;

        h1 = (h1 * base1 + x) % mod1;
        h2 = (h2 * base2 + x) % mod2;
    }

    return {h1, h2};
}

int main() {
    int n, m;
    cin >> n >> m;

    string text, pattern;
    cin >> text >> pattern;

    if(m > n) return 0;

    power1.resize(n + 1);
    power2.resize(n + 1);

    hash1.resize(n + 1);
    hash2.resize(n + 1);

    power1[0] = 1;
    power2[0] = 1;

    for(int i = 1; i <= n; i++) {
        power1[i] = power1[i - 1] * base1 % mod1;
        power2[i] = power2[i - 1] * base2 % mod2;
    }

    for(int i = 0; i < n; i++) {
        ll x = text[i] - 'a' + 1;

        hash1[i + 1] = (hash1[i] * base1 + x) % mod1;
        hash2[i + 1] = (hash2[i] * base2 + x) % mod2;
    }

    auto patternHash = get_hash(pattern);

    for(int i = 0; i <= n - m; i++) {

        int l = i;
        int r = i + m;

        ll h1 = (hash1[r] - hash1[l] * power1[m]) % mod1;
        ll h2 = (hash2[r] - hash2[l] * power2[m]) % mod2;

        if(h1 < 0) h1 += mod1;
        if(h2 < 0) h2 += mod2;

        if(h1 == patternHash.first && h2 == patternHash.second) {
            cout << i << " ";
        }
    }
}