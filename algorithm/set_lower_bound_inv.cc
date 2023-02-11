// https://atcoder.jp/contests/arc155/tasks/arc155_b

#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// set_lower_bound(st, x): stの中で、x以上の最小値を返す。
// set_lower_bound_inv(minus_st, x): stの中で、x以下の最大値を返す。
// minus_stは、stに逆の符号を付けたもの。
// st, minus_stにはINF, -INFを入れて、値が返るようにすること。
// 計算量: O(logN)
template<typename T> T set_lower_bound(const set<T>& st, T x) {
  auto it = st.lower_bound(x);
  assert(it != st.end());
  return (*it);
}
template<typename T> T set_lower_bound_inv(const set<T>& minus_st, T x) {
  auto it = minus_st.lower_bound(-x);
  assert(it != minus_st.end());
  return -(*it);
}

int main() {
  const long long INF = 2e9+2;
  int Q, A, B;
  cin >> Q >> A >> B;
  set<int> st;
  set<int> minus_st;
  st.insert(INF);
  st.insert(-INF);
  minus_st.insert(INF);
  minus_st.insert(-INF);
  auto add = [&](int a, int b) {
    st.insert(a + b);
    st.insert(a - b);
    minus_st.insert(-(a + b));
    minus_st.insert(-(a - b));
  };
  add(A, B);
  for (int q = 0; q < Q; q++) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      add(a, b);
    } else {
      int R = set_lower_bound(st, a);
      int L = set_lower_bound_inv(minus_st, b);
      if (R <= b && a <= L) {
        cout << 0 << '\n';
      } else {
        long long ans = INF;
        ans = min(ans, (long long)R - b);
        ans = min(ans, (long long)a - L);
        cout << ans << '\n';
      }
    }
  }
  return 0;
}
