// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=ja
// https://drken1215.hatenablog.com/entry/2018/06/08/210000

#include <iostream>
using namespace std;

// Solve ax + by = gcd(a, b)
int extended_euclid(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long d = extended_euclid(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

int main() {
  int a, b;
  cin >> a >> b;
  long long x, y;
  extended_euclid(a, b, x, y);
  cout << x << ' ' << y << endl;
  return 0;
}
