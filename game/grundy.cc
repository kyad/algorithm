// https://atcoder.jp/contests/abc255/tasks/abc255_g
// https://www.creativ.xyz/grundy-number-1065/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<long long> A(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
  map<long long, vector<long long> > ngs;
  for (int m = 0; m < M; m++) {
    long long X, Y;
    cin >> X >> Y;
    ngs[X].push_back(X - Y);
  }
  vector<long long> xs;  // 禁じ手がある座標
  vector<long long> gs;  // 禁じ手がある座標のGrundy数
  // Grundy数を求める関数
  auto grundy = [&](long long x) -> long long {
    int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();  // xにxsが入っているか調べたい
    if (i < xs.size() && xs[i] == x) {  // xがxsに入っていたら、メモした値を返す
      return gs[i];
    }
    // xが禁じ手でなければ、xから、xまでにある禁じ手の数を引いたものがGrundy数
    return x - i;
  };
  map<long long, int> cnt;  // Grundy数がgの個数の分布
  for (auto [x, ys] : ngs) {
    map<long long, int> mp;  // 行き先のGrundy数の分布
    for (long long y : ys) {
      mp[grundy(y)]++;
    }
    for (auto [g, num] : mp) {
      // gに行ける枝の数 = 1(絶対ある) + x以前にあったgの数 - xからgへの禁じ手の数
      // temp>0ならxのGrundy数はgではない。
      int temp = 1 + cnt[g] - num;
      if (temp == 0) {
        // xのGrundy数はg
        xs.push_back(x);
        gs.push_back(g);
        cnt[g]++;
        break;
      }
    }
  }
  long long total = 0;
  for (int n = 0; n < N; n++) {
    total ^= grundy(A.at(n));
  }
  if (total == 0) {
    cout << "Aoki" << endl;
  } else {
    cout << "Takahashi" << endl;
  }
  return 0;
}
