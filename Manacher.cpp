#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    string t = "^";

    for(char c : s) {
        t += '#';
        t += c;
    }

    t += "#$";

    int m = t.size();

    vector<int> p(m, 0);

    int r = 0;
    int c = 0;

    for(int i = 1; i < m - 1; i++) {

        if(i < r) {
            int mirror = 2 * c - i;
            p[i] = min(r - i, p[mirror]);
        }

        while(t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }

        if(i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }

    int best = 0;
    int center = 0;

    for(int i = 1; i < m - 1; i++) {
        if(p[i] > best) {
            best = p[i];
            center = i;
        }
    }

    int start = (center - best) / 2;

    cout << s.substr(start, best) << '\n';
}