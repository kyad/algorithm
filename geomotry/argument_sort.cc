// // https://atcoder.jp/contests/abc442/tasks/abc442_e

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// 偏角ソート
// r = y / x
struct Rat {
  int y;
  int x;
  int k;  // 象限
  Rat(int ay, int ax) : y(ay), x(ax) {  // (x, y)は原点でない
    if (x > 0 && y == 0) {
      k = 0;  // X軸上、X>0
    } else if (x > 0 && y > 0) {
      k = 1;  // 第一象限
    } else if (x == 0 && y > 0) {
      k = 2;  // Y軸上、Y>0
    } else if (x < 0 && y > 0) {
      k = 3;  // 第二象限
    } else if (x < 0 && y == 0) {
      k = 4;  // X軸上、X<0
    } else if (x < 0 && y < 0) {
      k = 5;  // 第三象限
    } else if (x == 0 && y < 0) {
      k = 6;  // Y軸上、Y<0
    } else if (x > 0 && y < 0) {
      k = 7;  // 第四象限
    } else {
      assert(false);
    }
  }
  friend bool operator<(const Rat &r0, const Rat &r1) {  // 偏角ソート順
    int k0 = r0.k;
    int k1 = r1.k;
    if (k0 != k1) {
      return k0 < k1;
    }
    // k0 == k1
    if (k0 == 0 || k0 == 2 || k0 == 4 || k0 == 6) {
      return false;
    }
    long long x0 = abs(r0.x);
    long long y0 = abs(r0.y);
    long long x1 = abs(r1.x);
    long long y1 = abs(r1.y);
    if (k0 == 1 || k0 == 5) {
      return y0 * x1 < y1 * x0;
    } else if (k0 == 3 || k1 == 7) {
      return x0 * y1 < x1 * y0;
    }
    assert(false);
  }
};

ostream& operator<<(ostream& os, const Rat &r) {
  os << "[" << r.y << " / " << r.x << "]" << r.k;
  return os;
}

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<Rat> Rs;  // ソート前
  vector<Rat> rs;
  for (int i = 0; i < N; i++) {
    int X, Y;
    cin >> X >> Y;
    Rat r(Y, X);
    Rs.push_back(r);
    rs.push_back(r);
  }
  sort(rs.begin(), rs.end());  // 偏角ソート
  for (int qi = 0; qi < Q; qi++) {
    int A, B;
    cin >> A >> B;
    A--; B--;
    Rat ra = Rs.at(A);
    Rat rb = Rs.at(B);
    int P = prev(upper_bound(rs.begin(), rs.end(), ra)) - rs.begin();
    int Q = prev(lower_bound(rs.begin(), rs.end(), rb)) - rs.begin();
    int ans;
    int a = upper_bound(rs.begin(), rs.end(), ra) - rs.begin();
    int b = upper_bound(rs.begin(), rs.end(), rb) - rs.begin();
    if (a >= b) {
      ans = P - Q;
    } else {
      ans = P + (N - Q);
    }
    cout << ans << '\n';
  }
  return 0;
}
