 while (head[u] != head[v]) {
    if (depth[head[u]] < depth[head[v]])
      swap(u, v);

    ans += query(1, 1, curPos, pos[head[u]], pos[u]);
    u = parent[head[u]];
  }