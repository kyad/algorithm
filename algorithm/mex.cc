// https://atcoder.jp/contests/typical90/tasks/typical90_ae

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/**
 * Mex(Aに含まれない最小の非負整数)を返す。
 * 計算量はO(M + N) (NはAの要素数)
 * \param[in] M: Aの最大値
 * \param[in] A: Mex計算対象の配列。値は0以上M以下であること。
 * \return AのMex(Aに含まれない最小の非負整数)。
 */
int mex_linear(int M, const vector<int> &A) {
  vector<bool> used(M + 1, false);
  for (size_t i = 0; i < A.size(); i++) {
    used.at(A.at(i)) = true;
  }
  int mex = 0;
  for (mex = 0; mex <= M; mex++) {
    if (!used.at(mex)) {
      break;
    }
  }
  return mex;
}

/**
 * Mex(Aに含まれない最小の非負整数)を返す。
 * 計算量はO(NlogN)
 * \param[in] A: Mex計算対象の配列。
 * \return AのMex(Aに含まれない最小の非負整数)。
 */
#include <algorithm>
template<class T> T mex(const vector<T> &A) {
  vector<T> B(A);
  sort(B.begin(), B.end());
  int mex = 0;
  for (size_t i = 0; i < B.size(); i++) {
    int b = B.at(i);
    if (b < mex) {
      continue;
    } else if (b == mex) {
      mex++;
      continue;
    } else {
      break;
    }
  }
  return mex;
}

vector<vector<int> > grundy(int W, int B) {
  int B_MAX = B + W * (W + 1) / 2;
  vector<vector<int> > g(W + 1, vector<int>(B_MAX + 1, 0));
  for (int w = 0; w <= W; w++) {
    for (int b = 0; b <= B_MAX; b++) {
      if (w == 0 && b <= 1) {
        continue;
      }
      vector<int> a;
      if (w >= 1 && b + w <= B_MAX) {
        a.push_back(g.at(w - 1).at(b + w));
      }
      for (int k = 1; k <= b / 2; k++) {
        a.push_back(g[w][b - k]);
      }
#if 1
      int M = (W + 1) * (B_MAX + 1) + 2;
      g[w][b] = mex_linear(M, a);
#else
      g[w][b] = mex(a);
#endif
    }
  }
  return g;
}

int main() {
  int N;
  cin >> N;
  vector<int> W(N);
  for (int n = 0; n < N; n++) {
    cin >> W.at(n);
  }
  vector<int> B(N);
  for (int n = 0; n < N; n++) {
    cin >> B.at(n);
  }
  int Wmax = *max_element(W.begin(), W.end());
  int Bmax = *max_element(B.begin(), B.end());
  vector<vector<int> > g = grundy(Wmax, Bmax);
  int g_all = 0;
  for (int n = 0; n < N; n++) {
    g_all ^= g[W[n]][B[n]];
  }
  if (g_all) {
    cout << "First" << endl;
  } else {
    cout << "Second" << endl;
  }
  return 0;
}
