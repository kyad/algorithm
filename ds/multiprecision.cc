// https://atcoder.jp/contests/arc146/tasks/arc146_a
// sudo apt install libboost-dev

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost;

// xをbase進数で見た時の桁数を返す
int digits(long long x, int base) { int d = 0; while (x > 0) { x /= base; d++; } return d; }

multiprecision::cpp_int value(int a, int b, int c) {
  string s = to_string(a) + to_string(b) + to_string(c);
  return multiprecision::cpp_int(s);
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
  // digit -> values
  map<int, multiset<int> > mp;
  for (int n = 0; n < N; n++) {
    int d = digits(A.at(n), 10);
    mp[-d].insert(-A.at(n));
  }
  vector<int> cand(3);
  for (int i = 0; i < 3; i++) {
    multiset<int>::iterator it = mp.begin()->second.begin();
    cand.at(i) = -(*it);
    mp.begin()->second.erase(it);
    if (mp.begin()->second.size() == 0) {
      mp.erase(mp.begin());
    }
  }
  vector<int> p = {0, 1, 2};
  multiprecision::cpp_int ans = 0;
  do {
    multiprecision::cpp_int now = value(cand[p[0]], cand[p[1]], cand[p[2]]);
    ans = max(ans, now);
  } while (next_permutation(p.begin(), p.end()));
  cout << ans << endl;
  return 0;
}
