// https://atcoder.jp/contests/abc032/tasks/abc032_c
// https://qiita.com/drken/items/ecd1a472d3a0e7db8dce

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  long long K;
  cin >> N >> K;
  vector<int> s(N);
  for (int n = 0; n < N; n++) {
    cin >> s.at(n);
    if (s.at(n) == 0) {
      cout << N << endl;
      return 0;
    }
  }
  // shakutori
  int ans = 0;
  long long prod = 1;
  int right = 0;
  for (int left = 0; left < N; left++) {
    while (right < N && prod * s.at(right) <= K) {
      prod *= s.at(right);
      right++;
    }
    ans = max(ans, right - left);
    if (right == left) {
      right++;
    } else {
      prod /= s.at(left);
    }
  }
  cout << ans << endl;
  return 0;
}
