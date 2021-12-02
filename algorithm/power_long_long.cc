// https://atcoder.jp/contests/abc228/tasks/abc228_e
// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a

#include <iostream>
using namespace std;

// m^n, O(log n)
long long power(long long m, long long n, int mod) {
  long long a = m % mod;
  long long ans = 1;
  while (n > 0) {
    if ((n & 1) == 1) {
      ans *= a;
      ans %= mod;
    }
    a *= a;
    a %= mod;
    n >>= 1;
  }
  return ans;
}

int main() {
  const int p = 998244353;
  long long N, K, M;
  cin >> N >> K >> M;
  if (M % p == 0) {
    cout << 0 << endl;
    return 0;
  }
  // ans = M ^ (K ^ N) (mod p) 
  // Mとpは互いに素だから、フェルマーの小定理より M ^ (p - 1) = 1 (mod p) なので
  // K ^ N = temp (mod p - 1) とおくと
  // ans = M ^ temp
  long long temp = power(K, N, p - 1);
  long long ans = power(M, temp, p);
  cout << ans << endl;
  return 0;
}
