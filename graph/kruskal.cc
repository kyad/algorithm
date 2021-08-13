// https://atcoder.jp/contests/abc065/tasks/arc076_b
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_1.cpp
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_4.cpp
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap15/code_15_1.cpp

#include <algorithm>
#include <iostream>
#include <vector>
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
  int N;
  cin >> N;
  vector<pair<int, int> > x(N);
  vector<pair<int, int> > y(N);
  for (int n = 0; n < N; n++) {
    cin >> x[n].first >> y[n].first;
    x[n].second = n;
    y[n].second = n;
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  vector<pair<int, pair<int, int> > > edges;
  for (int n = 0; n < N - 1; n++) {
    edges.push_back(make_pair(x[n + 1].first - x[n].first, make_pair(x[n].second, x[n + 1].second)));
    edges.push_back(make_pair(y[n + 1].first - y[n].first, make_pair(y[n].second, y[n + 1].second)));
  }
  // Kruskal's algorithm O(|E|log|V|)
  sort(edges.begin(), edges.end());
  long long weight = 0;
  UnionFind uf(N);
  for (size_t i = 0; i < edges.size(); i++) {
    int w = edges[i].first;
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    if (uf.issame(u, v)) {
      continue;
    }
    weight += w;
    uf.unite(u, v);
  }
  cout << weight << endl;
  return 0;
}
