#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];

int subtree[MAXN];
bool removed[MAXN];

// parent in centroid decomposition tree
int centroidParent[MAXN];

//--------------------------------------------------
// Step 1 : Calculate subtree sizes
//--------------------------------------------------

int getSubtreeSize(int node, int parent) {

    subtree[node] = 1;

    for (int child : adj[node]) {

        if (child == parent || removed[child])
            continue;

        subtree[node] += getSubtreeSize(child, node);
    }

    return subtree[node];
}

//--------------------------------------------------
// Step 2 : Find centroid
//--------------------------------------------------

int getCentroid(int node, int parent, int totalSize) {

    for (int child : adj[node]) {

        if (child == parent || removed[child])
            continue;

        if (subtree[child] > totalSize / 2)
            return getCentroid(child, node, totalSize);
    }

    return node;
}

//--------------------------------------------------
// Step 3 : Build centroid decomposition
//--------------------------------------------------

void build(int node, int parent) {

    int totalSize = getSubtreeSize(node, -1);

    int centroid = getCentroid(node, -1, totalSize);

    centroidParent[centroid] = parent;

    removed[centroid] = true;

    for (int child : adj[centroid]) {

        if (removed[child])
            continue;

        build(child, centroid);
    }
}

//--------------------------------------------------

int main() {

    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build(1, -1);

    cout << "Centroid Parent Array\n";

    for (int i = 1; i <= n; i++)
        cout << i << " -> " << centroidParent[i] << '\n';
}