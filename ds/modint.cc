// https://atcoder.jp/contests/abc232/tasks/abc232_e

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

// https://noshi91.hatenablog.com/entry/2019/03/31/174006
// modint
#include <cstdint>

template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &value() noexcept { return a; }
  constexpr const u64 &value() const noexcept { return a; }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = Modulus - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};

// debug
template <std::uint_fast64_t Modulus> ostream& operator<<(ostream& os, const modint<Modulus> &m) {
  os << m.a;
  return os;
}

int main() {
  int H, W, K;
  cin >> H >> W >> K;
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  vector<vector<vector<modint<MOD> > > > dp(K + 1, vector<vector<modint<MOD> > >(2, vector<modint<MOD> >(2, modint<MOD>(0))));
  dp[0][0][0] = 1;
  for (int k = 1; k <= K; k++) {
    dp[k][0][0] += dp[k - 1][0][1] * 1;
    dp[k][0][0] += dp[k - 1][1][0] * 1;

    dp[k][0][1] += dp[k - 1][0][0] * (W - 1);
    dp[k][0][1] += dp[k - 1][0][1] * (W - 2);
    dp[k][0][1] += dp[k - 1][1][1] * 1;

    dp[k][1][0] += dp[k - 1][0][0] * (H - 1);
    dp[k][1][0] += dp[k - 1][1][0] * (H - 2);
    dp[k][1][0] += dp[k - 1][1][1] * 1;

    dp[k][1][1] += dp[k - 1][0][1] * (H - 1);
    dp[k][1][1] += dp[k - 1][1][0] * (W - 1);
    dp[k][1][1] += dp[k - 1][1][1] * (H - 2 + W - 2);
  }
  dp[K][0][1] /= (W - 1);
  dp[K][1][0] /= (H - 1);
  dp[K][1][1] /= (W - 1);
  dp[K][1][1] /= (H - 1);
  cout << dp[K][x2 == x1 ? 0 : 1][y2 == y1 ? 0 : 1].a << endl;
  return 0;
}
