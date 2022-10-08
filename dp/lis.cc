// https://atcoder.jp/contests/arc149/tasks/arc149_b

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T> int lis(vector<T> X) {
  const int INF = 1e9 + 2;
  int n = X.size();
  // L[i] is the minimum last number of subsequence whose length is i
  vector<T> L(n + 1, INF);
  size_t len = 0;
  L.at(0) = -INF;
  for (int i = 0; i < n; i++) {
    vector<int>::iterator it = lower_bound(L.begin(), L.end(), X.at(i));
    size_t pos = distance(L.begin(), it);
    len = max(len, pos);
    *it = X.at(i);
  }
  return (int)len;
}

int main() {
  int N;
  cin >> N;
  vector<pair<int, int> > P(N);
  for (int n = 0; n < N; n++) {
    cin >> P.at(n).first;
  }
  for (int n = 0; n < N; n++) {
    cin >> P.at(n).second;
  }
  sort(P.begin(), P.end());
  vector<int> B(N);
  for (int n = 0; n < N; n++) {
    B.at(n) = P.at(n).second;
  }
  int ans = N + lis(B);
  cout << ans << endl;
  return 0;
}
