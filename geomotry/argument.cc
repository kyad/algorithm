// https://atcoder.jp/contests/typical90/tasks/typical90_i

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// argument
double rad2deg(double rad) { return rad * 180 / M_PI; }
template<typename T> double arg_rad(T x, T y) { return atan2(y, x); } // Returns [-pi, pi]
template<typename T> double arg_deg(T x, T y) { return rad2deg(arg_rad(x, y)); } // Returns [-180, 180]
// 2つの偏角のなす角
inline double angle_deg(double arg_deg0, double arg_deg1) {
  double a = arg_deg0 - arg_deg1;
  if (a < 0) {
    a += 360;
  }
  if (a > 180) {
    a = 360 - a;
  }
  return a;
}

int main() {
  int N;
  cin >> N;
  vector<int> X(N), Y(N);
  for (int n = 0; n < N; n++) {
    cin >> X.at(n) >> Y.at(n);
  }
  double ans = 0;
  for (int j = 0; j < N; j++) {
    vector<double> args;
    for (int i = 0; i < N; i++) {
      if (i == j) {
        continue;
      }
      int dx0 = X[i] - X[j];
      int dy0 = Y[i] - Y[j];
      args.push_back(arg_deg(dx0, dy0));
    }
    sort(args.begin(), args.end());
    const int M = args.size();
    for (size_t i = 0; i < M; i++) {
      double target = args[i] + 180;
      if (target > 180) {
        target -= 360;
      }
      vector<double>::iterator it = lower_bound(args.begin(), args.end(), target);
      int pos = it - args.begin();
      int idx0 = pos % M;
      int idx1 = (pos - 1 + M) % M;
      double cand0 = angle_deg(args[idx0], args[i]);
      double cand1 = angle_deg(args[idx1], args[i]);
      ans = max({ans, cand0, cand1});
    }
  }
  cout << setprecision(15) << ans << endl;
  return 0;
}
