// https://atcoder.jp/contests/abc262/tasks/abc262_e
// https://drken1215.hatenablog.com/entry/2018/06/08/210000

#include <iostream>
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

int main() {
  COMinit();
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> deg(N, 0);
  for (int m = 0; m < M; m++) {
    int U, V;
    cin >> U >> V;
    U--; V--;
    deg[U]++;
    deg[V]++;
  }
  int O = 0;  // 次数が奇数の頂点数
  int E = 0;  // 次数が偶数の頂点数
  for (int n = 0; n < N; n++) {
    if (deg[n] % 2) {
      O++;
    } else {
      E++;
    }
  }
  long long ans = 0;
  for (int o = 0; o <= K; o += 2) {
    int e = K - o;
    if (o > O || e > E) {
      continue;
    }
    ans += (COM(O, o) * COM(E, e)) % MOD;
    ans %= MOD;
  }
  cout << ans << endl;
  return 0;
}
