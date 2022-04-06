// https://atcoder.jp/contests/abc242/tasks/abc242_f

#include <iostream>
#include <vector>
using namespace std;

const int MAX = 2501;  // n (<= 10^7)
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
  int N, M, B, W;
  cin >> N >> M >> B >> W;
  COMinit();
  auto f = [&](int b) {
    // d[h][w]: h行, w列の領域に、石をb個置き、
    // 行も列も1個以上石が置かれている場合の数
    vector<vector<long long> > d(N + 1, vector<long long>(M + 1, 0));
    for (int h = 0; h <= N; h++) {
      for (int w = 0; w <= M; w++) {
        for (int i = 0; i <= h; i++) {  // i: 石が置かれていないことが確定していない行数
          for (int j = 0; j <= w; j++) {  // j: 石が置かれていないことが確定していない列数
            long long now;
            if (b > i * j) {
              now = 0;
            } else {
              now = COM(i * j, b);
            }
            now *= COM(h, i);
            now %= MOD;
            now *= COM(w, j);
            now %= MOD;
            if ((h - i + w - j) % 2) {
              now = MOD - now;  // now *= (-1);  // 包除原理
            }
            d[h][w] += now;
            d[h][w] %= MOD;
          }
        }
      }
    }
    return d;
  };
  auto db = f(B);
  auto dw = f(W);
            
  long long ans = 0;
  for (int bi = 0; bi <= N; bi++) {  // 黒を置く行の数
    for (int bj = 0; bj <= M; bj++) {  // 黒を置く列の数
      for (int wi = 0; wi <= N - bi; wi++) {  // 白を置く行の数
        for (int wj = 0; wj <= M - bj; wj++) {  // 白を置く列の数
          long long now = COM(N, bi);
          now *= COM(N - bi, wi);
          now %= MOD;
          now *= COM(M, bj);
          now %= MOD;
          now *= COM(M - bj, wj);
          now %= MOD;
          now *= db[bi][bj];
          now %= MOD;
          now *= dw[wi][wj];
          now %= MOD;
          ans += now;
          ans %= MOD;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
