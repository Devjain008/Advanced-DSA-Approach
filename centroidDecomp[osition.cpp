#include <bits/stdc++.h>
using namespace std;

class CDN {
    vector<vector<int>> adj;
    vector<int> centroid;
    vector<int> size;
    vector<int> removed;
    vector<int> best;
    vector<vector<pair<int, int>>> dist;

public:

    CDN(int n) {
        adj.resize(n + 1);
        centroid.resize(n + 1);
        size.resize(n + 1);
        removed.assign(n + 1, 0);
        best.assign(n + 1, INT_MAX);
        dist.resize(n + 1);
    }

    void addEdges(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void calculateSize(int node, int parent) {
        size[node] = 1;

        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            calculateSize(child, node);
            size[node] += size[child];
        }
    }

    int findCentroid(int node, int parent) {
        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            if(size[child] > size[node] / 2) {
                return findCentroid(child, node);
            }
        }

        return node;
    }

    void calculateDistance(int node, int parent, int depth, int centroidNode) {
        dist[node].push_back({centroidNode, depth});

        for(int child : adj[node]) {
            if(child == parent || removed[child]) continue;

            calculateDistance(child, node, depth + 1, centroidNode);
        }
    }

    void build(int node, int parent) {
        calculateSize(node, -1);

        int centroidNode = findCentroid(node, -1);

        calculateDistance(centroidNode, -1, 0, centroidNode);

        // Mark centroid as removed
        removed[centroidNode] = true;

        // Centroid tree parent
        centroid[centroidNode] = parent;

        // Decompose remaining components
        for(int child : adj[centroidNode]) {
            if(removed[child]) continue;

            build(child, centroidNode);
        }
    }

    void mark(int x) {
        for(auto [c, d] : dist[x]) {
            best[c] = min(best[c], d);
        }
    }

    int query(int x) {
        int ans = INT_MAX;

        for(auto [c, d] : dist[x]) {
            if(best[c] == INT_MAX) continue;

            ans = min(ans, best[c] + d);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    CDN cd(n);

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        cd.addEdges(u, v);
    }

    cd.build(1, -1);

    int q;
    cin >> q;

    while(q--) {
        int type, x;
        cin >> type >> x;

        if(type == 1) {
            cd.mark(x);
        }
        else {
            cout << cd.query(x) << '\n';
        }
    }

    return 0;
}