// https://atcoder.jp/contests/abc211/tasks/abc211_d
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_3.cpp

#include <bits/stdc++.h>
using namespace std;

int bfs(const vector<vector<int> > &graph, int s, int t) {
  int N = (int)graph.size();
  queue<int> todo;
  vector<int> dist(N, -1);
  vector<int> count(N, 0);
  dist[s] = 0;
  count[s] = 1;
  todo.push(s);
  while (!todo.empty()) {
    int v = todo.front();
    todo.pop();
    for (size_t i = 0; i < graph[v].size(); i++) {
      int x = graph[v][i];
      if (dist[x] < 0) {
	dist[x] = dist[v] + 1;
	todo.push(x);
      }
      if (dist[x] == dist[v] + 1) {  // 前に、vと同じ距離のノードからxに訪れていた場合の処理
	count[x] += count[v];
	count[x] %= 1000000007;  // MOD
      }
    }
  }
  return count[t];
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > graph(N);
  for (int i = 0; i < M; i++) {
    int A, B;
    cin >> A >> B;
    graph.at(A - 1).push_back(B - 1);
    graph.at(B - 1).push_back(A - 1);
  }
  int ans = bfs(graph, 0, N - 1);
  cout << ans << endl;
  return 0;
}
