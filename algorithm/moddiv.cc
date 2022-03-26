// https://atcoder.jp/contests/abc243/tasks/abc243_f

#include <iostream>
#include <vector>
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

// solve ay = b mod m (y = b / a), O(log m)
long long moddiv(long long b, long long a, int m) {
  long long ans = modinv(a, m) * b;
  ans %= m;
  return ans;
}

// facotial and inverse of factorial, O(N)
long long fact[51];  // n! = fact[n]
long long ifact[51];  // 1/(n!) = ifact[n]
void init_fact(int N, int mod) {
  fact[0] = 1;
  for (int n = 1; n <= N; n++) {
    fact[n] = fact[n - 1] * n;
    fact[n] %= mod;
  }
  ifact[N] = modinv(fact[N], mod);
  for (int n = N - 1; n >= 0; n--) {
    ifact[n] = ifact[n + 1] * (n + 1);
    ifact[n] %= mod;
  }
}

int main() {
  const int MOD = 998244353;
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> W(N);
  for (int n = 0; n < N; n++) {
    cin >> W.at(n);
  }
  long long Wsum = 0;
  for (int n = 0; n < N; n++) {
    Wsum += W.at(n);
    Wsum %= MOD;
  }
  vector<long long> p(N);
  for (int n = 0; n < N; n++) {
    p[n] = moddiv(W[n], Wsum, MOD);
  }
  // powp(n, k) = p[n] ^ k (k=0, 1, ..., K)
  vector<vector<long long> > powp(N, vector<long long>(K + 1, 1));
  for (int n = 0; n < N; n++) {
    for (int k = 1; k <= K; k++) {
      powp[n][k] = powp[n][k - 1] * p[n];
      powp[n][k] %= MOD;
    }
  }
  init_fact(K, MOD);
  // dp[i][j][k]: 商品i(1-indexed)までを見た時、N個からj種類選んで、合計k個選んだ時の確率の和
  vector<vector<vector<long long> > > dp(N + 1, vector<vector<long long> >(M + 1, vector<long long>(K + 1, 0)));
  dp[0][0][0] = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      for (int k = 0; k <= K; k++) {
        // iからi+1への配るdp
        int ni = i + 1;
        // i+1の時
        // 商品i+1を取らない時
        dp[ni][j][k] += dp[i][j][k];
        dp[ni][j][k] %= MOD;
        // 商品i+1を取る時
        int nj = j + 1;
        if (nj > M) {
          continue;
        }
        for (int d = 1; d <= K - k; d++) {
          int nk = k + d;
          // now = dp[i][j][k] * powp[i][d] * ifact[d]
          long long now = dp[i][j][k] * powp[i][d];
          now %= MOD;
          now *= ifact[d];
          now %= MOD;
          dp[ni][nj][nk] += now;
          dp[ni][nj][nk] %= MOD;
        }
      }
    }
  }
  long long ans = dp[N][M][K] * fact[K];
  ans %= MOD;
  cout << ans << endl;
  return 0;
}
