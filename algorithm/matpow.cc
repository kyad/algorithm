// https://atcoder.jp/contests/abc293/tasks/abc293_e

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/** 行列AとBの積を返す。計算量はO(NKM) */
template<class T>
vector<vector<T> > matmul(const vector<vector<T> > &A,
                          const vector<vector<T> > &B,
                          int mod = 0) {
  int N = A.size();
  int K = A.at(0).size();
  assert((int)B.size() == K);
  int M = B.at(0).size();
  vector<vector<T> > C(N, vector<T>(M, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < K; k++) {
        C.at(i).at(j) += A.at(i).at(k) * B.at(k).at(j);
        if (mod > 0) {
          C.at(i).at(j) %= mod;
        }
      }
    }
  }
  return C;
}

/** 行列Aのn乗を返す。計算量はO(N^3log(n)) */
template<class T> vector<vector<T> > matpow(const vector<vector<T> > &A, long long n, int mod = 0) {
  int N = A.size();
  assert((int)A.at(0).size() == N);
  if (n == 0) {
    vector<vector<T> > I(N, vector<T>(N, 0));
    for (int i = 0; i < N; i++) {
      I.at(i).at(i) = 1;
    }
    return I;
  }
  vector<vector<T> > B = matpow(A, n / 2, mod);
  vector<vector<T> > C = matmul(B, B, mod);
  if (n % 2) {
    C = matmul(C, A, mod);
  }
  return C;
}

int main() {
  int A, M;
  long long X;
  cin >> A >> X >> M;
  vector<vector<long long> > B = { {A, 1}, {0, 1} };
  vector<vector<long long> > C = matpow(B, X, M);
  cout << C[0][1] << endl;
  return 0;
}
