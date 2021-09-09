// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=ja

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int INF = 1000000001;
  int n;
  cin >> n;
  // L[i] is the minimum last number of subsequence whose length is i
  vector<int> L(n + 1, INF);
  size_t len = 0;
  L.at(0) = -1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    vector<int>::iterator it = lower_bound(L.begin(), L.end(), x);
    size_t pos = distance(L.begin(), it);
    len = max(len, pos);
    *it = x;
  }
  cout << len << endl;
  return 0;
}
