// https://atcoder.jp/contests/abc272/tasks/abc272_f

#include <iostream>
#include <vector>
using namespace std;
#include <atcoder/string>
using namespace atcoder;

int main() {
  int N;
  string S, T;
  cin >> N >> S >> T;
  string U = S + S + '$' + T + T + '~';
  vector<int> sa = suffix_array(U);
  long long s_num = 0;
  long long ans = 0;
  for (int i : sa) {
    if (0 <= i && i <= N - 1) {  // S
      s_num++;
    } else if (2 * N + 1 <= i && i <= 3 * N) {  // T
      ans += s_num;
    }
  }
  cout << ans << endl;
  return 0;
}
