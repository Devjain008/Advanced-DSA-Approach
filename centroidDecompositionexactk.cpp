#include <bits/stdc++.h>
using namespace std;

class Solution {
    int n, K;
    long long ans = 0;

    vector<vector<int>> adj;
    vector<int> sz;
    vector<bool> removed;

    void getSize(int node, int parent) {
        sz[node] = 1;

        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            getSize(child, node);
            sz[node] += sz[child];
        }
    }

    int getCentroid(int node, int parent, int total) {
        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            if(sz[child] > total / 2) {
                return getCentroid(child, node, total);
            }
        }

        return node;
    }

    void getDistances(int node, int parent, int depth, vector<int>& dist) {
        if(depth > K) return;

        dist.push_back(depth);

        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            getDistances(child, node, depth + 1, dist);
        }
    }

    void process(int centroid) {
        vector<int> freq(K + 1, 0);
        freq[0] = 1;

        for(int child : adj[centroid]) {
            if(removed[child]) continue;

            vector<int> dist;
            getDistances(child, centroid, 1, dist);

            for(int d : dist) {
                if(K - d >= 0) {
                    ans += freq[K - d];
                }
            }

            for(int d : dist) {
                freq[d]++;
            }
        }
    }

    void decompose(int node) {
        getSize(node, -1);

        int centroid = getCentroid(node, -1, sz[node]);

        process(centroid);

        removed[centroid] = true;

        for(int child : adj[centroid]) {
            if(removed[child]) continue;

            decompose(child);
        }
    }

public:
    long long countPairs(int N, int k, vector<vector<int>>& edges) {
        n = N;
        K = k;

        adj.assign(n + 1, {});
        sz.assign(n + 1, 0);
        removed.assign(n + 1, false);

        for(auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        ans = 0;
        decompose(1);

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;

    vector<vector<int>> edges(n - 1, vector<int>(2));

    for(int i = 0; i < n - 1; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    Solution sol;

    cout << sol.countPairs(n, K, edges) << '\n';

    return 0;
}