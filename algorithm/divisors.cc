#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
// modint
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;
ostream& operator<<(ostream& os, const mint &v) {
  os << v.val();
  return os;
}

// m^n, O(log n)
long long power(long long m, long long n, int mod = 998244353) {
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

/**
 * 2からNまでの非自明な約数のリストを返す。
 * 非自明な約数とは、1とNは含まないものとする。
 * 計算量：O(NlogN)
 * 答のサイズ：大雑把にはO(NlogN)。一つひとつはそれ以上の最小の高度合成数の約数の個数で見積る
 * \param N Input.
 * \param include1 trueにすると答に1を含める。
 * \return Answer. ans[M]にはM(1<=M<=N)の約数のリストが入っている。
 */
vector<vector<int> > divisors(int N, bool include1 = false) {
  vector<vector<int> > ans(N + 1);
  if (include1) {
    for (int n = 1; n <= N; n++) {
      ans.at(n).push_back(1);
    }
  }
  for (int p = 2; p <= N / 2; p++) {
    for (int n = p; n <= N; n += p) {
      ans.at(n).push_back(p);
    }
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  string S;
  cin >> S;
  
  auto solve = [&](int M) -> mint {
    vector<bool> a(M, true);
    for (int n = 0; n < N; n++) {
      if (S[n] == '.') {
        a[n % M] = false;
      }
    }
    int c1 = count(a.begin(), a.end(), true);
    mint ans = power(2, c1);
    return ans;
  };

  mint ans = 0;
  vector<mint> B(N + 1);
  vector<vector<int> > divs = divisors(N, true);
  for (int M : divs[N]) {
    mint A = solve(M);
    for (int d : divs[M]) {
      A -= B[d];
    }
    B[M] = A;
    ans += B[M];
  }
  cout << ans.val() << endl;
  return 0;
}
