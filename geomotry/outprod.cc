// https://atcoder.jp/contests/abc207/tasks/abc207_d

#include <algorithm>
#include <boost/rational.hpp>
#include <iostream>
#include <vector>
using namespace boost;
using namespace std;

typedef rational<int> rat;

template<class T> T magnitude2(T x, T y) {
  return x * x + y * y;
}

template<class T> T outprod2(T ax, T ay, T bx, T by) {
  return ax * by - ay * bx;
}

int main() {
  int N;
  cin >> N;
  if (N == 1) {
    cout << "Yes" << endl;
    return 0;
  }
  vector<int> A(N), B(N), C(N), D(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n) >> B.at(n);
  }
  for (int n = 0; n < N; n++) {
    cin >> C.at(n) >> D.at(n);
  }
  // Sは、0を基準点とし、0-->1を基準のベクトルとする
  int s_base_x = A[1] - A[0];
  int s_base_y = B[1] - B[0];
  int s_base_mag2 = magnitude2(s_base_x, s_base_y);
  // Sを特徴づける量を計算する
  vector<pair<rat, int> > s_pos, s_neg;
  vector<int> s_zero;
  for (int i = 2; i < N; i++) {
    int dx = A[i] - A[0];
    int dy = B[i] - B[0];
    int mag2 = magnitude2(dx, dy);
    int outp = outprod2(s_base_x, s_base_y, dx, dy);
    if (outp == 0) {
      s_zero.push_back(mag2);
    } else {
      rat sin2(outp * outp, s_base_mag2 * mag2);
      if (outp > 0) {
        s_pos.push_back(make_pair(sin2, mag2));
      } else {
        s_neg.push_back(make_pair(sin2, mag2));
      }
    }
  }
  sort(s_zero.begin(), s_zero.end());
  sort(s_pos.begin(), s_pos.end());
  sort(s_neg.begin(), s_neg.end());
  // Tは、iを基準点とし、i-->jを基準のベクトルとする
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) {
        continue;
      }
      // base length
      int t_base_x = C[j] - C[i];
      int t_base_y = D[j] - D[i];
      int t_base_mag2 = magnitude2(t_base_x, t_base_y);
      if (s_base_mag2 != t_base_mag2) {
        continue;
      }
      // Tを特徴づける量を計算する
      vector<pair<rat, int> > t_pos, t_neg;
      vector<int> t_zero;
      for (int k = 0; k < N; k++) {
        if (k == i || k == j) {
          continue;
        }
        int dx = C[k] - C[i];
        int dy = D[k] - D[i];
        int mag2 = magnitude2(dx, dy);
        int outp = outprod2(t_base_x, t_base_y, dx, dy);
        if (outp == 0) {
          t_zero.push_back(mag2);
        } else {
          rat sin2(outp * outp, t_base_mag2 * mag2);
          if (outp > 0) {
            t_pos.push_back(make_pair(sin2, mag2));
          } else {
            t_neg.push_back(make_pair(sin2, mag2));
          }
        }
      }
      sort(t_zero.begin(), t_zero.end());
      sort(t_pos.begin(), t_pos.end());
      sort(t_neg.begin(), t_neg.end());
      if (s_zero != t_zero || s_pos != t_pos || s_neg != t_neg) {
        continue;
      }
      cout << "Yes" << endl;
      return 0;
    }
  }
  cout << "No" << endl;
  return 0;
}
