// https://atcoder.jp/contests/abc368/tasks/abc368_f
// https://www.creativ.xyz/grundy-number-1065/

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
  int N;
  cin >> N;
  vector<int> A(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
  vector<int> stones(N);  // 石の個数
  for (int i = 0; i < N; i++) {
    stones.at(i) = (int)prime_factorization(A.at(i)).size();
  }
  // N山Nim
  int sum = 0;
  for (int i = 0; i < N; i++) {
    sum ^= stones.at(i);
  }
  string ans;
  if (sum != 0) {
    ans = "Anna";
  } else {
    ans = "Bruno";
  }
  cout << ans << endl;
  return 0;
}
