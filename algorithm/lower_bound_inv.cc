#include <cassert>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// v.lower_bound(x): vの中で、x以上の最小のイテレータを返す。
// lower_bound_inv(minus_v, x): vの中で、x以下の最大の値を返す。
// minus_v配列vに逆の符号を付けてソートしたもの。
// 計算量: O(logN)
#include <algorithm>
template<class T> T lower_bound_inv(const vector<T> &minus_v, T x) {
  auto it = lower_bound(minus_v.begin(), minus_v.end(), -x);
  return -(*it);
}

int main() {
  int N;
  cin >> N;
  vector<pair<int, int> > lr;
  vector<int> minus_lens;
  for (int i = 1; i <= 11; i++) {
    int len = (1<<i) - 1;
    for (int l = 1; l <= N; l++) {
      int r = l + len - 1;
      if (r > N) {
        continue;
      }
      lr.push_back(make_pair(l, r));
    }
    minus_lens.push_back(-len);
  }
  sort(minus_lens.begin(), minus_lens.end());
  int M = lr.size();
  assert(M <= 50000);
  map<pair<int, int>, int> mp;  // lr inverse
  for (int i = 0; i < M; i++) {
    int l = lr[i].first;
    int r = lr[i].second;
    mp[make_pair(l, r)] = i;
  }
  cout << M << endl;
  for (int m = 0; m < M; m++) {
    cout << lr[m].first << ' ' << lr[m].second << '\n';
  }
  // Phase 2
  int Q;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    int L, R;
    cin >> L >> R;
    int len = lower_bound_inv(minus_lens, R - L + 1);
    pair<int, int> a = make_pair(L, L + len - 1);
    assert(mp.count(a) > 0);
    int ai = mp[a];
    pair<int, int> b = make_pair(R - len + 1, R);
    assert(mp.count(b) > 0);
    int bi = mp[b];
    ai++; bi++;
    cout << ai << ' ' << bi << '\n';
  }
  return 0;
}
