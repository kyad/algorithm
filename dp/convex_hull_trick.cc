// https://atcoder.jp/contests/dp/tasks/dp_z
// https://kazuma8128.hatenablog.com/entry/2018/02/28/102130
// https://www.slideshare.net/hcpc_hokudai/convex-hull-trick

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// Li Chao Segment Tree (Convex Hull Trick)
// 直線の追加クエリと、最大値の取得クエリをそれぞれO(logN)で処理する。
// idには-INFを指定する。
// 最小値の取得の場合は、insertで(-a, -b)を指定し、getの符号を反転する。
template <typename T, const T id> class convex_hull_trick {
  struct line {
    T a, b;
    line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
    T get(T x) { return a * x + b; }
  };
  struct node {
    line l;
    node *lch, *rch;
    node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
    ~node() {
      if (lch) delete lch;
      if (rch) delete rch;
    }
  };
private:
  const int n;
  const vector<T> pos;
  node *root;
public:
  // pos_(サイズN): 最大値クエリを取る点。小→大でソート済み
  convex_hull_trick(const vector<T>& pos_) : n(pos_.size()), pos(pos_), root(nullptr) {}
  ~convex_hull_trick() { if (root) delete root; }
  void insert(T a, T b) { line l(a, b); root = modify(root, 0, n - 1, l); }
  T get(T x) const {
    int t = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
    assert(t < n && pos[t] == x);
    return sub(root, 0, n - 1, t);
  }
private:
  node *modify(node *p, int lb, int ub, line& l) {
    if (!p) { return new node(l); }
    if (p->l.get(pos[lb]) >= l.get(pos[lb]) && p->l.get(pos[ub]) >= l.get(pos[ub])) { return p; }
    if (p->l.get(pos[lb]) <= l.get(pos[lb]) && p->l.get(pos[ub]) <= l.get(pos[ub])) { p->l = l; return p; }
    int c = (lb + ub) / 2;
    if (p->l.get(pos[c]) < l.get(pos[c])) { swap(p->l, l); }
    if (p->l.get(pos[lb]) <= l.get(pos[lb])) {
      p->lch = modify(p->lch, lb, c, l);
    } else {
      p->rch = modify(p->rch, c + 1, ub, l);
    }
    return p;
  }
  T sub(node *p, int lb, int ub, int t) const {
    if (!p) { return id; }
    if (ub - lb == 0) { return p->l.get(pos[t]); }
    int c = (lb + ub) / 2;
    if (t <= c) { return max(p->l.get(pos[t]), sub(p->lch, lb, c, t)); }
    else { return max(p->l.get(pos[t]), sub(p->rch, c + 1, ub, t)); }
  }
};

int main() {
  int N;
  long long C;
  cin >> N >> C;
  vector<long long> H(N);
  for (int n = 0; n < N; n++) {
    cin >> H.at(n);
  }
  const long long INF = 1e18;
  convex_hull_trick<long long, -INF> cht(H);
  vector<long long> dp(N, 0);
  for (int i = 0; i < N; i++) {
    if (i == 0) {
      dp[0] = 0;
    } else {
      dp[i] = -cht.get(H[i]) + H[i] * H[i] + C;
    }
    long long A = -2LL * H[i];
    long long B = dp[i] + H[i] * H[i];
    cht.insert(-A, -B);
  }
  cout << dp[N - 1] << endl;
  return 0;
}
