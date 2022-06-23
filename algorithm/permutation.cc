// https://atcoder.jp/contests/abc226/tasks/abc226_f

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MAX = 510000;  // n (<= 10^7)
const int MOD = 998244353;  // p (prime, > n)

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

// nPk mod p, O(1)
long long PERM(int n, int k) {
  if (n < k) {
    return 0;
  }
  if (n < 0 || k < 0) {
    return 0;
  }
  return (fac[n] * finv[n - k]) % MOD;
}

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

// 最小公倍数
int LCM(int a, int b) {
  return a / __gcd(a, b) * b;
}

int main() {
  int N, K;
  cin >> N >> K;
  COMinit();
  // dp[i][l]: i個使ってLCMがlの個数
  vector<map<int, long long> > dp(N + 1);
  dp[0][1] = 1;
  for (int i = 0; i < N; i++) {
    map<int, long long> mp(dp[i]);
    for (map<int, long long>::iterator it = mp.begin(); it != mp.end(); it++) {
      int l = it->first;
      long long x = it->second;
      for (int j = 1; i + j <= N; j++) {
        // j個追加する遷移。
        // 遷移する時は、残りの番号のうち最小のものを必ず取るようにする。
        long long now = x * PERM(N - i - 1, j - 1);
        now %= MOD;
        dp[i + j][LCM(l, j)] += now;
        dp[i + j][LCM(l, j)] %= MOD;
      }
    }
  }
  long long ans = 0;
  for (map<int, long long>::iterator it = dp[N].begin(); it != dp[N].end(); it++) {
    int l = it->first;  // score
    int x = it->second;  // count
    long long now = power(l, K, MOD) * x;
    now %= MOD;
    ans += now;
    ans %= MOD;
  }
  cout << ans << endl;
  return 0;
}
