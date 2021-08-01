// https://atcoder.jp/contests/abc212/tasks/abc212_d

#include <bits/stdc++.h>
using namespace std;

int main() {
  priority_queue<long long, vector<long long>, greater<long long> > pq;
  int Q;
  cin >> Q;
  long long offset = 0;
  for (int q = 0; q < Q; q++) {
    int P;
    cin >> P;
    if (P == 1) {
      long long X;
      cin >> X;
      pq.push(X - offset);
    } else if (P == 2) {
      long long X;
      cin >> X;
      offset += X;
    } else {
      long long value = pq.top();
      cout << (value + offset) << endl;
      pq.pop();
    }
  }
  return 0;
}
