// https://atcoder.jp/contests/abc217/tasks/abc217_b

#include <bits/stdc++.h>
using namespace std;

int main() {
  set<string> s;
  s.insert("ABC");
  s.insert("ARC");
  s.insert("AGC");
  s.insert("AHC");
  for (int i = 0; i < 3; i++) {
    string S;
    cin >> S;
    s.erase(S);
  }
  cout << *s.begin() << endl;
  return 0;
}
