// https://atcoder.jp/contests/typical90/tasks/typical90_bw

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/**
 * 素因数分解して結果を重複も込めて小さい順に返す。
 * 計算量: O(sqrt(N))
 * 制約: Tはint, unsigned int, long long, unsigned long longのいずれか
 * \param N 素因数分解する数
 * \return vector<T> 素因数の配列。重複も込める。小さい順。1は含めない
 */
template<typename T> vector<T> prime_factorization(T N) {
  vector<T> ans;
  for (long long m = 2; m * m <= (long long)N; m++) {  // Care for overflow
    while (N % m == 0) {
      N /= m;
      ans.push_back(m);
    }
  }
  if (N != 1) {
    ans.push_back(N);
  }
  return ans;
}

int main() {
  long long N;
  cin >> N;
  vector<long long> ps = prime_factorization(N);
  int x = ps.size() - 1;
  int ans = 0;
  while (x > 0) {
    x >>= 1;
    ans++;
  }
  cout << ans << endl;
  return 0;
}
