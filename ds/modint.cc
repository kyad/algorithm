// https://atcoder.jp/contests/abc224/tasks/abc224_f
// https://noshi91.hatenablog.com/entry/2019/03/31/174006
// https://qiita.com/uesho/items/1ee5c3e665c72c035880

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &value() noexcept { return a; }
  constexpr const u64 &value() const noexcept { return a; }
  constexpr modint operator-() const noexcept { return modint(-a); }
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
  constexpr modint operator/(const long long rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator+=(const long long rhs) noexcept {
    modint<Modulus> b = modint<Modulus>(rhs);
    (*this) += b;
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator-=(const long long rhs) noexcept {
    modint<Modulus> b = modint<Modulus>(rhs);
    (*this) -= b;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator*=(const long long rhs) noexcept {
    modint<Modulus> b = modint<Modulus>(rhs);
    (*this) *= b;
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
  constexpr modint &operator/=(long long rhs) noexcept {
    modint<Modulus> b = modint<Modulus>(rhs);
    (*this) /= b;
    return *this;
  }
  constexpr modint &operator++() noexcept {
    a++;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator--() noexcept {
    if (a == 0) {
      a += Modulus;
    }
    a--;
    return *this;
  }
  modint pow(long long t) const {
    assert(t >= 0);
    if (!t) return 1;
    modint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }
  friend ostream& operator<<(ostream& os, const modint& m) {
    os << m.a;
    return os;
  }
};

int main() {
  string str;
  cin >> str;
  int N = str.size();
  vector<int> S(N + 1, 0);  // 1-indexed
  for (int n = 0; n < N; n++) {
    S.at(n + 1) = str[n] - '0';
  }
  vector<modint<MOD> > dp(N + 1, 0);  // dp[i]: iまで見た時の和。1-indexed
  vector<modint<MOD> > sum(N + 1, 0);  // dp[1]からdp[i]までの和。1-indexed
  vector<modint<MOD> > T(N + 1, 0);  // 1-indexed
  for (int i = 1; i <= N; i++) {
    modint<MOD> two = 2;
    modint<MOD> pow2 = two.pow(i - 1);
    T[i] = T[i - 1] * 10 + pow2 * S[i];
    dp[i] = sum[i - 1] + T[i];
    sum[i] = dp[i] + sum[i - 1];
  }
  cout << dp[N] << endl;
  return 0;
}
