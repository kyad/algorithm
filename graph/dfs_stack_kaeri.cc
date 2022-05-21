// https://atcoder.jp/contests/abc251/tasks/abc251_f

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

void dfs(int N, vector<vector<int> >& graph) {
  vector<bool> seen(N, false);  // todoに入れたことがあるか(訪問していないこともある)
  vector<bool> finished(N, false);  // 訪問したか
  stack<pair<int, int> > todo;
  todo.push(make_pair(0, -1));
  while (!todo.empty()) {
    int u = todo.top().first;
    int parent = todo.top().second;
    if (!finished.at(u) && parent >= 0) {  // 帰りがけ順で処理する代わりに、行きがけで初めて訪問した時に処理する
      cout << (parent + 1) << ' ' << (u + 1) << endl;
    }
    seen.at(u) = true;
    todo.pop();
    for (size_t i = 0; i < graph[u].size(); i++) {
      int v = graph[u][i];
      if (seen.at(v)) {
        continue;
      }
      todo.push(make_pair(v, u));
    }
    finished.at(u) = true;
  }
}  

void bfs(int N, vector<vector<int> >& graph) {
  queue<int> todo;
  vector<int> dist(N, -1);  // 訪問したか、訪問したならその距離
  todo.push(0);
  dist.at(0) = 0;
  while (!todo.empty()) {
    int u = todo.front();
    todo.pop();
    for (size_t i = 0; i < graph[u].size(); i++) {
      int v = graph[u][i];
      if (dist.at(v) < 0) {
        dist.at(v) = dist.at(u) + 1;
        todo.push(v);
        cout << (u + 1) << ' ' << (v + 1) << endl;
      }
    }
  }
}  

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > graph(N);
  for (int m = 0; m < M; m++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    graph.at(u).push_back(v);
    graph.at(v).push_back(u);
  }
  dfs(N, graph);
  bfs(N, graph);
  return 0;
}
