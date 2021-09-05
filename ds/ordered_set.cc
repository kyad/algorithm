// https://atcoder.jp/contests/abc217/tasks/abc217_d

#include <iostream>
#include <set>
using namespace std;

int main() {
  int L, Q;
  set<int> s;
  cin >> L >> Q;
  s.insert(0);
  s.insert(L);
  for (int q = 0; q < Q; q++) {
    int c, x;
    cin >> c >> x;
    if (c == 1) {
      s.insert(x); // log(Q)
    } else {
      set<int>::iterator it = s.lower_bound(x); // log(Q)
      cout << (*it - *prev(it)) << endl;
    }
  }
  return 0;
}
