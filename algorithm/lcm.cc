// https://atcoder.jp/contests/abc150/tasks/abc150_d

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 最小公倍数
long long LCM(int a, int b) {
  return (long long)a / __gcd(a, b) * b;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> a(N);
  for (int n = 0; n < N; n++) {
    cin >> a.at(n);
  }
  vector<int> b(N);
  for (int n = 0; n < N; n++) {
    b.at(n) = a.at(n) / 2;
  }
  long long L = 1;
  for (int n = 0; n < N; n++) {
    L = LCM((int)L, b.at(n));
    if (L > M) {
      cout << 0 << endl;
      return 0;
    }
    // L <= M <= 10^9 < INT_MAX
  }
  for (int n = 0; n < N; n++) {
    if ((L / b.at(n)) % 2 == 0) {
      cout << 0 << endl;
      return 0;
    }
  }
  // L <= 2 * M <= 2 * 10^9 < INT_MAX, 2 * L might be > INT_MAX
  long long U = ((long long)M - L) / (2 * L);
  cout << U + 1 << endl;
  return 0;
}
