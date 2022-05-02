// https://atcoder.jp/contests/abc246/tasks/abc246_f

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using mint = modint998244353;

int main() {
  int N, L;
  cin >> N >> L;
  vector<string> S(N);
  for (int n = 0; n < N; n++) {
    cin >> S.at(n);
  }
  mint ans = 0;
  for (int b = 1; b < (1<<N); b++) {
    string now;
    for (int i = 0; i < 26; i++) {
      now.push_back('a' + i);
    }
    for (int n = 0; n < N; n++) {
      if (((b >> n)&1) == 0) {
        continue;
      }
      // ソート済のnowとS.at(n)の共通部分をsに入れる
      string s;
      set_intersection(now.begin(), now.end(), S.at(n).begin(), S.at(n).end(), inserter(s, s.end()));
      now = s;
    }
    // 包除原理
    mint temp = now.size();
    if (__builtin_popcount(b) % 2) {
      ans += temp.pow(L);
    } else {
      ans -= temp.pow(L);
    }
  }
  cout << ans.val() << endl;
  return 0;
}
