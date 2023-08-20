// https://atcoder.jp/contests/typical90/tasks/typical90_cf

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/**
 * ランレングス符号化
 * 計算量: O(N)
 * \param[in] A: 符号化対象のvector
 * \return vector<pair<int, T> > : 符号化結果
 */
template<class T> vector<pair<int, T> > runlength(vector<T> A) {
  vector<pair<int, T> > ans;
  if (A.empty()) {
    return ans;
  }
  T now = A.at(0);
  int count = 1;
  for (size_t n = 1; n < A.size(); n++) {
    if (now == A.at(n)) {
      count++;
    } else {
      ans.push_back(make_pair(count, now));
      count = 1;
      now = A.at(n);
    }
  }
  if (count > 0) {
    ans.push_back(make_pair(count, now));
  }
  return ans;
}

/**
 * 文字列に対するランレングス符号化
 * 計算量: O(N)
 * \param[in] S: 符号化対象の文字列
 * \return vector<pair<int, char> > : 符号化結果
 */
vector<pair<int, char> > runlength(string S) {
  vector<char> A(S.size());
  for (size_t i = 0; i < S.size(); i++) {
    A.at(i) = S.at(i);
  }
  return runlength(A);
}

long long comb2(long long N) {
  return N * (N - 1) / 2;
}

int main() {
  long long N;
  string S;
  cin >> N >> S;
  long long ans = comb2(N);
  vector<pair<int, char> > r = runlength(S);
  for (auto [n, c] : r) {
    ans -= comb2(n);
  }
  cout << ans << endl;
  return 0;
}
