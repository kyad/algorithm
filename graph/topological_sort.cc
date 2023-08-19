// https://atcoder.jp/contests/abc223/tasks/abc223_d

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > graph(N);
  vector<int> indeg(N, 0);
  for (int m = 0; m < M; m++) {
    int A, B;
    cin >> A >> B;
    A--;
    B--;
    indeg.at(B)++;
    graph[A].push_back(B);
  }
  // Topological sort
  // 入力：uがvに依存する時、vからuに有向辺を張ったグラフ(uとvの向きに注意)。
  // 出力：先にやるべきタスクの順にノード番号を返す。
  //priority_queue<int> todo;
  priority_queue<int, vector<int>, greater<int> > todo;  // Lexical order
  for (int n = 0; n < N; n++) {
    if (indeg.at(n) == 0) {
      todo.push(n);
    }
  }
  vector<int> ans;
  while (!todo.empty()) {
    int u = todo.top();
    todo.pop();
    ans.push_back(u);
    for (size_t i = 0; i < graph.at(u).size(); i++) {
      int v = graph.at(u).at(i);
      indeg.at(v)--;
      if (indeg.at(v) == 0) {
        todo.push(v);
      }
    }
  }
  // Check if graph have loop
  if (ans.size() != (size_t)N) {
    cout << -1 << endl;
    return 0;
  }
  for (size_t i = 0; i < ans.size(); i++) {
    cout << (ans[i] + 1) << (i == (ans.size() - 1) ? '\n' : ' ');
  }
  return 0;
}
