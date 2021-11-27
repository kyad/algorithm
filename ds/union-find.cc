// https://atcoder.jp/contests/abc229/tasks/abc229_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_1.cpp
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_4.cpp

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

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > graph(N);
  for (int m = 0; m < M; m++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
  }
  vector<int> ans(N, 0);
  UnionFind uf(N);
  int num = 0;  // Union-Findの連結成分数
  for (int n = N - 1; n > 0; n--) {
    num++;
    for (size_t i = 0; i < graph[n].size(); i++) {
      int u = graph[n][i];
      if (uf.unite(n, u)) {
        num--;
      }
    }
    ans[n - 1] = num;
  }
  for (int n = 0; n < N; n++) {
    cout << ans[n] << endl;
  }
  return 0;
}
