// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
// https://qiita.com/drken/items/b97ff231e43bce50199a

#include <iostream>
using namespace std;

// Solve ax = 1 mod m  (m != prime is OK), O(log m)
// Solve ay = b mod m --> y = b * x mod m
long long modinv(long long a, long long m) {
  long long b = m, u = 1, v = 0;
  while (b) {
    long long t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) {
    u += m;
  }
  return u;
}

int main() {
  const int MOD = 1000000007;
  long long a = 12345678900000;
  long long b = 100000;
  a %= MOD;
  cout << a * modinv(b, MOD) % MOD << endl;

  for (int i = 0; i < 13; i++) {
    cout << i << ' ' << modinv(i, 13) << endl;
  }

  return 0;
}
