// https://atcoder.jp/contests/abc075/tasks/abc075_c
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_1.cpp
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_4.cpp

#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
  vector<int> parent, _size;

  UnionFind(int n) : parent(n, -1), _size(n, 1) {}

  int root(int x) {
    if (parent[x] == -1) {
      return x;
    } else {
      //return root(parent[x]);
      return parent[x] = root(parent[x]);
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

int main() {
  int N, M;
  cin >> N >> M;
  vector<pair<int, int> > graph;
  for (int m = 0; m < M; m++) {
    int a, b;
    cin >> a >> b;
    graph.push_back(make_pair(a - 1, b - 1));
  }
  int ans = 0;
  for (int m = 0; m < M; m++) {
    UnionFind uf(N);
    for (int e = 0; e < M; e++) {
      if (e == m) {
        continue;
      }
      uf.unite(graph.at(e).first, graph.at(e).second);
    }
    int count = 0;
    for (int n = 0; n < N; n++) {
      if (uf.root(n) == n) {
        count++;
      }
    }
    if (count == 2) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
