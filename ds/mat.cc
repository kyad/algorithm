// https://atcoder.jp/contests/dp/tasks/dp_r
// https://pione.hatenablog.com/entry/2021/04/04/231809

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<long long> > Mat;

// A * B, O(m * k * n)
Mat matmul_mod(Mat A, Mat B, int MOD) {
  size_t m = A.size();
  size_t k = B.size();
  size_t n = B[0].size();
  assert(A[0].size() == k);
  Mat C(m, vector<long long>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int l = 0; l < k; l++) {
        long long temp = (A[i][l] * B[l][j]) % MOD;
        C[i][j] += temp;
        C[i][j] %= MOD;
      }
    }
  }
  return C;
}

// A^n, O(m^3*logn)
Mat mat_power(Mat A, long long n, int mod) {
  size_t m = A.size();
  assert(A[0].size() == m);
  Mat a = A;
  Mat ans(m, vector<long long>(m, 0));
  for (int i = 0; i < m; i++) {
    ans[i][i] = 1;
  }
  while (n > 0) {
    if ((n & 1) == 1) {
      ans = matmul_mod(ans, a, mod);
    }
    a = matmul_mod(a, a, mod);
    n >>= 1;
  }
  return ans;
}

// 2d-matrix
template<class T> ostream& operator<<(ostream& os, const vector<vector<T> > &v) {
  size_t y0 = 0;
  size_t y1 = v.size() - 1;
  for (size_t i = y0; i <= y1; i++) {
    os << (i == 0 ? "[[" : " [");
    size_t x0 = 0;
    size_t x1 = v[i].size() - 1;
    for (size_t j = x0; j <= x1; j++) {
      os << v[i][j];
      if (j != x1) {
        os << ' ';
      }
    }
    os << (i == y1 ? "]]" : "]\n");
  }
  return os;
}

int main() {
  const int MOD = 1000000007;
  int N;
  long long K;
  cin >> N >> K;
  Mat A(N, vector<long long>(N, 0));
  for (int u = 0; u < N; u++) {
    for (int v = 0; v < N; v++) {
      cin >> A[u][v];
    }
  }
  A = mat_power(A, K, MOD);
  long long ans = 0;
  for (int u = 0; u < N; u++) {
    for (int v = 0; v < N; v++) {
      ans += A[u][v];
      ans %= MOD;
    }
  }
  cout << ans << endl;
  return 0;
}
