// https://atcoder.jp/contests/abc256/tasks/abc256_e

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> X(N);
  for (int n = 0; n < N; n++) {
    cin >> X.at(n);
    X.at(n)--;
  }
  vector<int> C(N);
  for (int n = 0; n < N; n++) {
    cin >> C.at(n);
  }
  // Functional graphのループ検出
  // 0: まだ訪れていない
  // 1: 今のDFSで探索中
  // 2: 探索完了
  vector<int> state(N, 0);
  // DFS
  vector<int> loop;
  // 返り値：もしループを発見したらループの最初の点(>=0)、そうでなければ-1
  auto dfs = [&](auto dfs, int u) -> int {
    state[u] = 1;
    int v = X[u];
    int ret;
    if (state[v] == 1) {  // ループを見つけた
      loop.push_back(u);
      ret = v;
    } else if (state[v] == 2) {  // ループ外だと分かった
      ret = -1;
    } else {
      ret = dfs(dfs, v);
      if (ret >= 0) {
        loop.push_back(u);
      }
      if (ret == u) {
        ret = -1;  // uはループの入口なので、その前はループではない
      }
    }
    state[u] = 2;
    return ret;
  };
  long long ans = 0;
  for (int n = 0; n < N; n++) {
    loop.clear();
    dfs(dfs, n);
    if (loop.size() > 0) {
      int now = 1000000001;
      for (size_t i = 0; i < loop.size(); i++) {
        int u = loop[i];
        now = min(now, C[u]);
      }
      ans += now;
    }
  }
  cout << ans << endl;
  return 0;
}
