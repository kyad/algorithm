// https://atcoder.jp/contests/abc296/tasks/abc296_e

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int u = 0; u < N; u++) {
    cin >> A.at(u);
    A.at(u)--;
  }

  // Functional graphのループ検出
  // 0: まだ訪れていない
  // 1: 今のDFSで探索中
  // 2: 探索完了
  vector<int> state(N, 0);
  // DFS
  vector<bool> in_loop(N, false);  // ループ内ならtrue、ループ外ならfalse
  // 返り値：もしループを発見したらループの最初の点(>=0)、そうでなければ-1
  auto dfs = [&](auto dfs, int u) -> int {
    state[u] = 1;
    int v = A[u];
    int ret;
    if (state[v] == 1) {  // ループを見つけた
      if (u == v) {
        ret = -1;  // 自己ループの場合
      } else {
        ret = v;
      }
      in_loop[v] = true;
    } else if (state[v] == 2) {  // ループ外だと分かった
      ret = -1;
    } else {
      ret = dfs(dfs, v);
      if (ret == u) {
        ret = -1;  // uはループの入口なので、その前はループではない
      }
    }
    if (ret >= 0) {
      in_loop[u] = true;
    }
    state[u] = 2;
    return ret;
  };

  for (int u = 0; u < N; u++) {
    if (state[u] == 0) {
      dfs(dfs, u);
    }
  }

  int ans = count(in_loop.begin(), in_loop.end(), true);
  cout << ans << endl;
  return 0;
}
