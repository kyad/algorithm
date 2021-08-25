// https://atcoder.jp/contests/abc034/tasks/abc034_c
// https://drken1215.hatenablog.com/entry/2018/06/08/210000

#include <iostream>
using namespace std;

const int MAX = 510000;  // n (<= 10^7)
const int MOD = 1000000007;  // p (prime, > n)

long long fac[MAX];  // a! mod p
long long finv[MAX];  // (a!)^{-1} mod p
long long inv[MAX];  // a^{-1} mod p

// O(n)
void COMinit() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < MAX; i++) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

// nCk mod p, O(1)
long long COM(int n, int k) {
  if (n < k) {
    return 0;
  }
  if (n < 0 || k < 0) {
    return 0;
  }
  return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

int main() {
  int W, H;
  cin >> W >> H;
  COMinit();
  cout << COM(W + H - 2, W - 1) << endl;
  return 0;
}
