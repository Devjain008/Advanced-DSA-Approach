// Count numbers from 0 to N whose digit sum equals K.
// #include <bits/stdc++.h>
// using namespace std;

// int digitSum(int n) {
//     int sum = 0;
    
//     while(n > 0) {
//         sum += n % 10;
//         n /= 10;
//     }
    
//     return sum;
// }

// int main() {
// // 	int n, k;
// // 	cin >> n >> k;
	
// // 	int cnt = 0;
	
// // 	for(int i = 0; i <= n; i++) {
// // 	    if(digitSum(i) == k) cnt++;
// // 	}
	
// // 	cout << cnt << "\n";

// }

// Count numbers from 0 to N that do not contain the digit 4.


// #include <bits/stdc++.h>
// using namespace std;

// string s;
// vector<vector<long long>> dp;

// long long f(int pos, int tight) {
//     if(pos == (int)s.size()) return 1;

//     if(dp[pos][tight] != -1) {
//         return dp[pos][tight];
//     }

//     int limit = tight ? s[pos] - '0' : 9;
//     long long ans = 0;

//     for(int d = 0; d <= limit; d++) {
//         if(d == 4) continue;

//         ans += f(pos + 1, tight && (d == s[pos] - '0'));
        
//     }

//     return dp[pos][tight] = ans;
// }

// int main() {
//     long long n;
//     cin >> n;

//     s = to_string(n);
//     dp.assign(s.size(), vector<long long>(2, -1));

//     cout << f(0, 1) << '\n';

//     return 0;
// }

// Count numbers in [L,R] that contain no two consecutive equal digits.

// #include <bits/stdc++.h>
// using namespace std;

// string s;
// long long dp[20][2][11][2];

// long long f(int pos, int tight, int prev, int started) {
//     if(pos == (int)s.size()) return 1;

//     long long &res = dp[pos][tight][prev][started];

//     if(res != -1) return res;

//     res = 0;

//     int limit = tight ? s[pos] - '0' : 9;

//     for(int d = 0; d <= limit; d++) {
//         int newTight = tight && (d == s[pos] - '0');

//         if(!started && d == 0) {
//             res += f(pos + 1, newTight, 10, 0);
//         } else {
//             if(started && d == prev) continue;

//             res += f(pos + 1, newTight, d, 1);
//         }
//     }

//     return res;
// }

// long long countValid(long long n) {
//     if(n < 0) return 0;

//     s = to_string(n);
//     memset(dp, -1, sizeof(dp));

//     return f(0, 1, 10, 0);
// }

// int main() {
//     long long L, R;
//     cin >> L >> R;

//     cout << countValid(R) - countValid(L - 1) << '\n';

//     return 0;
// }

// Count numbers in [L,R] whose digit sum is divisible by K.


// #include <bits/stdc++.h>
// using namespace std;

// string s;
// int K;
// vector<vector<vector<long long>>> dp;

// long long f(int pos, int tight, int rem) {
//     if(pos == (int)s.size()) {
//         return rem == 0;
//     }

//     long long &ans = dp[pos][tight][rem];

//     if(ans != -1) return ans;

//     ans = 0;

//     int limit = tight ? s[pos] - '0' : 9;

//     for(int d = 0; d <= limit; d++) {
//         int newTight = tight && (d == s[pos] - '0');
//         int newRem = (rem + d) % K;

//         ans += f(pos + 1, newTight, newRem);
//     }

//     return ans;
// }

// long long countValid(long long n, int k) {
//     if(n < 0) return 0;

//     s = to_string(n);
//     K = k;

//     dp.assign(s.size(), vector<vector<long long>>(
//         2, vector<long long>(K, -1)
//     ));

//     return f(0, 1, 0);
// }

// int main() {
//     long long L, R;
//     int K;
//     cin >> L >> R >> K;

//     cout << countValid(R, K) - countValid(L - 1, K) << '\n';

//     return 0;
// }

// Count numbers in [L,R] that contain exactly K occurrences of digit 7.

// #include <bits/stdc++.h>
// using namespace std;

// string s;
// int K;

// vector<vector<vector<long long>>> dp;

// long long f(int pos, int tight, int cnt) {
//     if(cnt > K) return 0;

//     if(pos == (int)s.size()) {
//         return cnt == K;
//     }

//     long long &ans = dp[pos][tight][cnt];

//     if(ans != -1) return ans;

//     ans = 0;

//     int limit = tight ? s[pos] - '0' : 9;

//     for(int d = 0; d <= limit; d++) {
//         int newTight = tight && (d == s[pos] - '0');
//         int newCnt = cnt + (d == 7);

//         ans += f(pos + 1, newTight, newCnt);
//     }

//     return ans;
// }

// long long countValid(long long n, int k) {
//     if(n < 0) return 0;

//     s = to_string(n);
//     K = k;

//     dp.assign(s.size(), vector<vector<long long>>(
//         2, vector<long long>(K + 2, -1)
//     ));

//     return f(0, 1, 0);
// }

// int main() {
//     long long L, R;
//     int K;
//     cin >> L >> R >> K;

//     cout << countValid(R, K) - countValid(L - 1, K) << '\n';

//     return 0;
// }

// Count numbers in `[L,R]` that contain only distinct no


// #include <bits/stdc++.h>
// using namespace std;

// string s;
// long long dp[20][2][1024][2];
// bool vis[20][2][1024][2];

// long long f(int pos, int tight, int mask, int started) {
//     if(pos == (int)s.size()) return 1;

//     if(vis[pos][tight][mask][started]) {
//         return dp[pos][tight][mask][started];
//     }

//     vis[pos][tight][mask][started] = true;

//     long long ans = 0;
//     int limit = tight ? s[pos] - '0' : 9;

//     for(int d = 0; d <= limit; d++) {
//         int newTight = tight && (d == s[pos] - '0');

//         if(!started && d == 0) {
//             ans += f(pos + 1, newTight, mask, 0);
//         } else {
//             if(mask & (1 << d)) continue;

//             ans += f(pos + 1, newTight, mask | (1 << d), 1);
//         }
//     }

//     return dp[pos][tight][mask][started] = ans;
// }

// long long countValid(long long n) {
//     if(n < 0) return 0;

//     s = to_string(n);
//     memset(vis, false, sizeof(vis));

//     return f(0, 1, 0, 0);
// }

// int main() {
//     long long L, R;
//     cin >> L >> R;

//     cout << countValid(R) - countValid(L - 1) << '\n';

//     return 0;
// }
