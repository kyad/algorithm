// https://atcoder.jp/contests/abc249/tasks/abc249_f

#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  int M = N + 1;
  vector<int> T(M), Y(M);
  // 全てのt=1の操作を無視する場合をケア
  T.at(0) = 1;
  Y.at(0) = 0;
  for (int n = 0; n < N; n++) {
    cin >> T.at(n + 1) >> Y.at(n + 1);
  }
  int k = K;
  const long long INF = 1000000000LL * 2 * 100000 + 1;
  long long ans = -INF;
  long long sum = 0;  // 下から見た時のt=2に対するyの総和
  multiset<int> st;  // t=2に対する負のyを小さいものからk個持つ。st内では-1倍して管理する
  long long st_sum = 0;  // stの合計(こちらは-1倍していない)
  auto push = [&](int x) {  // stにxを追加する
    st.insert(-x);
    st_sum += x;
  };
  auto pop = [&](int k) {  // stの個数がkを越えていれば大きいものから削除してk個にする
    while (st.size() > k) {
      int value = *st.begin();
      st_sum -= (-value);
      st.erase(st.begin());
    }
  };
  for (int m = M - 1; m >= 0; m--) {
    if (k < 0) {
      continue;
    }
    if (T.at(m) == 1) {
      long long now = (long long)Y.at(m) + sum - st_sum;
      ans = max(ans, now);
      k--;
      pop(k);
    } else {
      sum += Y.at(m);
      if (Y.at(m) < 0) {
        push(Y.at(m));
        pop(k);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
