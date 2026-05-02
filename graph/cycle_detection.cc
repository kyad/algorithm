// https://atcoder.jp/contests/abc456/tasks/abc456_e

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool cycle_detection(const vector<vector<int>> &graph) {
  int N = graph.size();
  // ループ検出付き有向グラフに対するdfs
  // ループを検出した時にtrueを返す
  // https://drken1215.hatenablog.com/entry/2023/05/20/200517
  vector<bool> seen(N, false);  // 行き掛け時の探索完了フラグ
  vector<bool> finished(N, false);  // 帰り掛け時の探索完了フラグ
  auto dfs = [&](auto dfs, int u) -> bool {
    seen.at(u) = true;  // 行き掛け時の訪問済(訪問完了)
    // if () {
    //   return;
    // }
    for (int v : graph.at(u)) {
      if (finished.at(v)) {
        continue;
      }
      if (seen.at(v) && !finished.at(v)) {
        return true;
      }
      if (dfs(dfs, v)) {
        return true;
      }
    }
    finished.at(u) = true;  // 帰り掛け時の訪問済(訪問完了)
    return false;
  };
  bool ans = false;
  for (int u = 0; u < N; u++) {
    if (dfs(dfs, u)) {
      ans = true;
    }
  }
  return ans;
}

int main() {
  int T;
  cin >> T;
  for (int ti = 0; ti < T; ti++) {
    int N, M;
    cin >> N >> M;
    vector<int> U(M), V(M);
    vector<vector<int> > G(N);
    for (int j = 0; j < M; j++) {
      int U, V;
      cin >> U >> V;
      U--; V--;
      G.at(U).push_back(V);
      G.at(V).push_back(U);
    }
    int W;
    cin >> W;
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
      cin >> S.at(i);
    }
    auto encode = [&](int u, int w) { return u + w * N; };
    auto decode = [&](int z) {
      int u = z % N;
      int w = z / N;
      return make_pair(u, w);
    };
    // (u, w)の拡大グラフ
    vector<vector<int>> graph(N * W);
    for (int u = 0; u < N; u++) {
      for (int w = 0; w < W; w++) {
        // (u, w)から遷移できる所に有向辺を張る
        int z = encode(u, w);
        int nw = (w + 1) % W;
        // とどまる
        if (S.at(u).at(w) == 'o' && S.at(u).at(nw) == 'o') {
          graph.at(z).push_back(encode(u, nw));
        }
        // 移動する
        for (int v : G.at(u)) {
          if (S.at(u).at(w) == 'o' && S.at(v).at(nw) == 'o') {
            graph.at(z).push_back(encode(v, nw));
          }
        }
      }
    }

    bool ans = cycle_detection(graph);
    cout << (ans ? "Yes" : "No") << '\n';
  }
  return 0;
}
