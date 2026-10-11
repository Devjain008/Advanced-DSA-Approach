// Given a string, construct its suffix array.

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     string s;
//     cin >> s;

//     vector<int> sa(n);

//     for(int i = 0; i < n; i++) {
//         sa[i] = i;
//     }

//     sort(sa.begin(), sa.end(), [&](int i, int j) {
//         return s.substr(i) < s.substr(j);
//     });

//     for(int i = 0; i < n; i++) {
//         cout << sa[i] << " ";
//     }

//     cout << '\n';

//     return 0;
// }

// longest prefix

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     string s;
//     cin >> s;

//     vector<int> lps(n, 0);

//     int len = 0;
//     int i = 1;

//     while(i < n) {
//         if(s[i] == s[len]) {
//             len++;
//             lps[i] = len;
//             i++;
//         }
//         else if(len != 0) {
//             len = lps[len - 1];
//         }
//         else {
//             lps[i] = 0;
//             i++;
//         }
//     }

//     for(int x : lps) {
//         cout << x << " ";
//     }
//     cout << '\n';

//     return 0;
// }

// Construct the LCP array using the suffix array.

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     string s;
//     cin >> s;

//     vector<int> sa(n);
//     iota(sa.begin(), sa.end(), 0);

//     // Construct suffix array using sort() and substr()
//     sort(sa.begin(), sa.end(), [&](int i, int j) {
//         return s.substr(i) < s.substr(j);
//     });

    // // rank[i] = position of suffix i in the suffix array
    // vector<int> rank(n);

    // for(int i = 0; i < n; i++) {
    //     rank[sa[i]] = i;
    // }

    // // Construct LCP array using Kasai's algorithm
    // vector<int> lcp(n, 0);
    // int k = 0;

    // for(int i = 0; i < n; i++) {
    //     int pos = rank[i];

        // if(pos == 0) {
        //     k = 0;
        //     continue;
        // }

        // int j = sa[pos - 1];

        // while(i + k < n && j + k < n &&
        //       s[i + k] == s[j + k]) {
        //     k++;
        // }

        // lcp[pos] = k;

//   

// Count the number of distinct substrings in a string.

// Find the longest repeated substring in a string.

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     string s;
//     cin >> s;

//     vector<int> sa(n);
//     iota(sa.begin(), sa.end(), 0);

//     // Step 1: Construct suffix array
//     sort(sa.begin(), sa.end(), [&](int i, int j) {
//         return s.substr(i) < s.substr(j);
//     });

//     // Step 2: Construct rank array
//     vector<int> rank(n);

//     for(int i = 0; i < n; i++) {
//         rank[sa[i]] = i;
//     }

//     // Step 3: Construct LCP array using Kasai's algorithm
//     vector<int> lcp(n, 0);
//     int k = 0;

//     for(int i = 0; i < n; i++) {
//         int pos = rank[i];

//         if(pos == 0) {
//             k = 0;
//             continue;
//         }

//         int j = sa[pos - 1];

    //     while(i + k < n && j + k < n &&
    //           s[i + k] == s[j + k]) {
    //         k++;
    //     }

    //     lcp[pos] = k;

    //     if(k > 0) {
    //         k--;
    //     }
    // }

    // // Step 4: Find the longest repeated substring
    // int maxLen = 0;
    // int start = -1;

    // for(int i = 1; i < n; i++) {
//         if(lcp[i] > maxLen) {
//             maxLen = lcp[i];
//             start = sa[i];
//         }
//     }

//     if(maxLen == 0) {
//         cout << "No repeated substring\n";
//     } else {
//         cout << s.substr(start, maxLen) << '\n';
//         cout << "Length: " << maxLen << '\n';
//     }

//     return 0;
// }

// Given a string and q patterns, determine whether each pattern occurs in the string using binary search over the suffix array.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.size();

    vector<int> sa(n);
    iota(sa.begin(), sa.end(), 0);

    // Build suffix array
    sort(sa.begin(), sa.end(), [&](int i, int j) {
        return s.substr(i) < s.substr(j);
    });

    int q;
    cin >> q;

    while(q--) {
        string p;
        cin >> p;

        int low = 0, high = n - 1;
        bool found = false;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            string suffix = s.substr(sa[mid]);

            if(suffix.compare(0, p.size(), p) == 0) {
                found = true;
                break;
            }

            if(suffix < p) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << (found ? "YES" : "NO") << '\n';
    }

    return 0;
}