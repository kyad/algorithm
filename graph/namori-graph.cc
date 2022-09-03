// https://atcoder.jp/contests/abc266/tasks/abc266_f

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > graph;

struct UnionFind {
  vector<int> parent, _size;

  UnionFind(int n) : parent(n, -1), _size(n, 1) {}

  int root(int x) {
    if (parent[x] == -1) {
      return x;
    } else {
      //return root(parent[x]);  // O(logN)
      return parent[x] = root(parent[x]);  // O(alpha(N))
    }
  }

  bool issame(int x, int y) {
    return root(x) == root(y);
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) {
      return false;
    }
    if (_size[x] < _size[y]) {
      swap(x, y);  // Union by size
    }
    parent[y] = x;
    _size[x] += _size[y];
    return true;
  }

  int size(int x) {
    return _size[root(x)];
  }
};

// Find loop for Namori graph
vector<bool> is_loop;
vector<bool> visited;
int dfs(int u, int parent) {
  visited.at(u) = true;
  for (size_t i = 0; i < graph.at(u).size(); i++) {
    int v = graph.at(u).at(i);
    if (v == parent) {
      continue;
    }
    if (visited.at(v)) {
      is_loop.at(u) = true;
      return v;
    }
    int w = dfs(v, u);
    if (w == -1) {
      continue;
    }
    is_loop.at(u) = true;
    if (w == u) {
      return -1;
    }
    return w;
  }
  return -1;
}
  
int main() {
  int N;
  cin >> N;
  graph.resize(N);
  vector<int> U(N), V(N);
  for (int n = 0; n < N; n++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
    U.at(n) = u;
    V.at(n) = v;
  }
  is_loop.resize(N, false);
  visited.resize(N, false);
  dfs(0, -1);
  UnionFind uf(N);
  for (int u = 0; u < N; u++) {
    for (size_t i = 0; i < graph.at(u).size(); i++) {
      int v = graph.at(u).at(i);
      if (is_loop.at(u) && is_loop.at(v)) {
        continue;
      }
      uf.unite(u, v);
    }
  }
  int Q;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    if (uf.issame(x, y)) {
      cout << "Yes" << '\n';
    } else {
      cout << "No" << '\n';
    }
  }
  return 0;
}
