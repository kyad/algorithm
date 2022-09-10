// https://atcoder.jp/contests/arc147/tasks/arc147_b

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template<class T> static size_t argmin(vector<T>& A, size_t a, size_t b) {
  size_t ans = a;
  T mn = A.at(a);
  for (size_t i = a + 1; i <= b; i++) {
    if (A.at(i) < mn) {
      ans = i;
      mn = A.at(i);
    }
  }
  return ans;
}

/**
 * Aをバブルソートし、手順を返す。
 *
 * 計算量: O(N^2)
 * @param[in,out] A ソート対象の配列。[0, N)の順列でなくても良いし、重複があっても良い。関数呼び出し後、Aはソートされる。
 * @return vector<int> ソート手順を順に返す。0-indexedで、(i, i+1)をswapする時はiが格納される。
 */
template<class T> vector<int> bubble_sort(vector<T>& A) {
  vector<int> ans;
  int N = A.size();
  for (int i = 0; i < N; i++) {
    int j = argmin(A, i, N - 1);
    for (int k = j - 1; k >= i; k--) {
      ans.push_back(k);
      swap(A.at(k), A.at(k + 1));
    }
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  vector<int> P(N);
  for (int n = 0; n < N; n++) {
    cin >> P.at(n);
    P.at(n)--;
  }

  vector<int> even;
  vector<int> odd;
  for (int n = 0; n < N; n++) {
    if (n % 2 == 0 && P[n] % 2 == 1) {
      even.push_back(n);
    } else if (n % 2 == 1 && P[n] % 2 == 0) {
      odd.push_back(n);
    }
  }
  assert(even.size() == odd.size());

  vector<pair<char, int> > ans;
  for (size_t k = 0; k < even.size(); k++) {
    int e = even[k];
    int o = odd[k];
    while (abs(e - o) > 1) {
      int i = max(e, o);
      assert(i >= 2);
      ans.push_back(make_pair('B', i - 2));
      if (e > o) {
        e -= 2;
      } else {
        o -= 2;
      }
      swap(P[i - 2], P[i]);
    }
    ans.push_back(make_pair('A', min(e, o)));
    swap(P[e], P[o]);
  }

  for (int k = 0; k < 2; k++) {
    vector<int> A;
    for (int i = k; i < N; i += 2) {
      A.push_back(P[i]);
    }
    vector<int> now = bubble_sort(A);
    for (int idx : now) {
      ans.push_back(make_pair('B', idx * 2 + k));
    }
  }

  size_t S = ans.size();
  assert(S <= 100000);
  
  cout << S << '\n';
  for (size_t i = 0; i < S; i++) {
    cout << ans[i].first << ' ' << (ans[i].second + 1) << '\n';
  }
  return 0;
}
