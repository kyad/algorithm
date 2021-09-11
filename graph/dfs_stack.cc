// https://atcoder.jp/contests/abc138/tasks/abc138_d
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_2.cpp

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<vector<int> >graph(N);
  for (int n = 0; n < N - 1; n++) {
    int a, b;
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }
  vector<int> X(N, 0);
  for (int q = 0; q < Q; q++) {
    int p, x;
    cin >> p >> x;
    X[p - 1] += x;
  }
  // DFS
  vector<bool> seen(N, false);
  stack<pair<int, int> > todo;
  todo.push(make_pair(0, 0));
  vector<int> ans(N);
  while (!todo.empty()) {
    int u = todo.top().first;
    int value = todo.top().second;
    seen[u] = true;
    todo.pop();
    value += X[u];
    ans[u] = value;
    for (size_t i = 0; i < graph[u].size(); i++) {
      int v = graph[u][i];
      if (seen[v]) {
        continue;
      }
      todo.push(make_pair(v, value));
    }
  }
  for (int n = 0; n < N; n++) {
    cout << ans[n] << (n == N - 1 ? '\n' : ' ');
  }
  return 0;
}
