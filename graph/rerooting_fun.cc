// https://atcoder.jp/contests/abc222/tasks/abc222_f
// https://atcoder.jp/contests/abc222/editorial/2749

#include <iostream>
#include <vector>
using namespace std;

template <typename Cost>
struct Edge {
  int src, to;
  Cost cost;
  Edge(int s, int t, Cost c = 1) : src(s), to(t), cost(c) {}
  operator int() const { return to; }
};
template <typename Cost>
struct Graph : vector<vector<Edge<Cost>>> {
  Graph(int n) : vector<vector<Edge<Cost>>>(n) {}
  void add_edge(int s, int t, Cost c = 1) { (*this)[s].emplace_back(s, t, c); }
};

template <typename Cost, typename Data, Data (*merge)(Data, Data), Data (*e)(),
          Data (*leaf)(), Data (*apply)(Data, int, int, Cost)>
struct Rerooting : Graph<Cost> {
  vector<Data> dp, memo;

  Rerooting(int n) : Graph<Cost>::Graph(n) {}

  vector<Data> run() {
    memo.resize((*this).size(), e());
    dp.resize((*this).size());
    dfs1(0, -1);
    dfs2(0, -1, e());
    return dp;
  }

  void dfs1(int c, int p) {
    bool upd = false;
    for (Edge<Cost> &d : (*this)[c]) {
      if (d == p) continue;
      dfs1(d, c);
      upd = true;
      memo[c] = merge(memo[c], apply(memo[d], d, c, d.cost));
    }
    if (!upd) memo[c] = leaf();
  }

  void dfs2(int c, int p, const Data &val) {
    vector<Data> ds{val};
    for (Edge<Cost> &d : (*this)[c]) {
      if (d == p) continue;
      ds.push_back(apply(memo[d], d, c, d.cost));
    }
    int n = ds.size(), idx = 1;
    vector<Data> head(n + 1, e()), tail(n + 1, e());
    for (int i = 0; i++ < n;) head[i] = merge(head[i - 1], ds[i - 1]);
    for (int i = n; i-- > 0;) tail[i] = merge(tail[i + 1], ds[i]);
    dp[c] = head[n];
    for (Edge<Cost> &d : (*this)[c]) {
      if (d == p) continue;
      Data sub = merge(head[idx], tail[idx + 1]);
      dfs2(d, c, apply(sub, c, d, d.cost));
      idx++;
    }
  }
};

using Data = long long;  // DPの型
using Cost = long long;  // 重さ

vector<Data> D;

Data merge(Data a, Data b) { return max(a, b); }  // 累積計算の2項演算。結合則が成り立つこと。
Data e() { return 0; }  // mergeに対する単位元
Data leaf() { return 0; }  // 末端の値
Data apply(Data a, int c, int d, Cost w) { return max(D[c] + w, a + w); }  // dから、c(dp値a、重みw)に行く時のdpへの寄与。dp[c]がmerge(dp[c], apply(...))に更新される。

int main() {
  int N;
  cin >> N;
  D.resize(N);
  Rerooting<Cost, Data, merge, e, leaf, apply> rerooting(N);
  for (int n = 0; n < N - 1; n++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--;
    rerooting.add_edge(a, b, c);
    rerooting.add_edge(b, a, c);
  }
  for (int n = 0; n < N; n++) {
    cin >> D.at(n);
  }
  vector<Data> dp = rerooting.run();
  for (int n = 0; n < N; n++) {
    cout << dp[n] << endl;
  }
  return 0;
}
