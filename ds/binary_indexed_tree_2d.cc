// https://atcoder.jp/contests/abc311/tasks/abc311_f

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// modint
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;
ostream& operator<<(ostream& os, const mint &v) {
  os << v.val();
  return os;
}

template<class T> struct binary_indexed_tree_2d {
  int H, W;
  vector<vector<T> > bit;
  binary_indexed_tree_2d() {}
  binary_indexed_tree_2d(int h, int w) : H(h), W(w) {
    bit.assign(H + 1, vector<T>(W + 1, 0));
  }
  void resize(int h, int w) {
    H = h;
    W = w;
    bit.assign(H + 1, vector<T>(W + 1, 0));
  }
  // Add a to bit[y][x], O(logH * logW). y, x: 1-indexed
  void add1(int y, int x, T a) {
    for (int Y = y; Y <= H; Y += (Y & -Y)) {
      for (int X = x; X <= W; X += (X & -X)) {
        bit[Y][X] += a;
      }
    }
  }
  // Add a to bit[y][x], O(logH * logW). y, x: 0-indexed
  void add0(int y, int x, T a) { add1(y + 1, x + 1, a); }
  // Returns sum of bit[Y][X] for 1 <= Y <= y, 1 <= X <= x, O(logH * logW). y, x: 1-indexed
  T sum1(int y, int x) {
    T ret = 0;
    for (int Y = y; Y > 0; Y -= (Y & -Y)) {
      for (int X = x; X > 0; X -= (X & -X)) {
        ret += bit[Y][X];
      }
    }
    return ret;
  }
  // Returns sum of bit[Y][X] for 0 <= Y <= y, 0 <= X <= x, O(logH * logW). y, x: 0-indexed
  // 半開区間の場合は[0, y)*[0, x)の少なくとも一方の軸が空集合の場合にも使え、0を返す。
  T sum0(int y, int x) { return sum1(y + 1, x + 1); }
  T sum0_open(int y, int x) { return (y == 0 || x == 0) ? 0 : sum0(y - 1, x - 1); }
  // Returns sum of bit[Y][X] for y0 <= Y <= y1, x0 <= X <= x1, O(logH * logW). y0, y1, x0, x1: 1-indexed
  T sum1(int y0, int x0, int y1, int x1) {
    return sum1(y1, x1) - sum1(y1, x0 - 1) - sum1(y0 - 1, x1) + sum1(y0 - 1, x0 - 1);
  }
  // Returns sum of bit[Y][X] for y0 <= Y <= y1, x0 <= X <= x1, O(logH * logW). y0, y1, x0, x1: 0-indexed
  // 半開区間の場合は[y0, y1)*[x0, x1)の少なくとも一方の軸が空集合の場合にも使え、0を返す。
  T sum0(int y0, int x0, int y1, int x1) { return sum1(y0 + 1, x0 + 1, y1 + 1, x1 + 1); }
  T sum0_open(int y0, int x0, int y1, int x1) { return (y0 == y1 || x0 == x1) ? 0 : sum0(y0, x0, y1 - 1, x1 - 1); }
};
// Example
// binary_indexed_tree_2d<int> bit(N, M);
// 1点(y, x)の取得：sum0(y, x, y, x)

int main() {
  int N, M;
  cin >> N >> M;
  vector<string> S(N);
  for (int n = 0; n < N; n++) {
    cin >> S.at(n);
  }
  // bfs
  queue<pair<int, int> > todo;
  vector<vector<int> > dist(N, vector<int>(M, -1));
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < M; x++) {
      if (S[y][x] == '#') {
        dist[y][x] = 0;
        todo.push(make_pair(y, x));
      }
    }
  }
  while (!todo.empty()) {
    const pair<int, int> u = todo.front();
    todo.pop();
    const int y = u.first;
    const int x = u.second;
    for (int dx = 0; dx <= 1; dx++) {
      const int ny = y + 1;
      const int nx = x + dx;
      if (ny >= N || nx >= M) {
        continue;
      }
      if (dist[ny][nx] < 0) {
        dist[ny][nx] = dist[y][x] + 1;
        todo.push(make_pair(ny, nx));
      }
    }
  }

  vector<vector<mint> > dp(N, vector<mint>(M, 0));
  binary_indexed_tree_2d<mint> bit(N, M);
  
  for (int x = M - 1; x >= 0; x--) {
    for (int y = 0; y < N; y++) {
      if (dist[y][x] >= 0) {
        break;
      }
      if (y + 1 < N && x + 1 < M && dist[y + 1][x + 1] < 0) {  // 右下が白の時
        dp[y][x] = bit.sum0_open(0, x + 1, y + 2, x + 2);
      } else {  // 右下が黒の時
        dp[y][x] = bit.sum0_open(0, x + 1, N, M) + 1;
      }
      bit.add0(y, x, dp[y][x]);
    }
  }
  mint ans = 1;  // 塗らない
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < M; x++) {
      ans += dp[y][x];
    }
  }
  cout << ans.val() << endl;
  return 0;
}
