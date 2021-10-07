// https://atcoder.jp/contests/joi2011ho/tasks/joi2011ho1
// https://atcoder.jp/contests/abc221/editorial/2718
// https://algo-logic.info/binary-indexed-tree/

#include <iostream>
#include <vector>
using namespace std;

struct binary_indexed_tree_2d {
  int H, W;
  vector<vector<int> > bit;
  binary_indexed_tree_2d() {}
  binary_indexed_tree_2d(int h, int w) : H(h), W(w) {
    bit.assign(H + 1, vector<int>(W + 1, 0));
  }
  void resize(int h, int w) {
    H = h;
    W = w;
    bit.assign(H + 1, vector<int>(W + 1, 0));
  }
  // Add a to bit[y][x], O(logH * logW)
  // y, x: 1-indexed
  void add(int y, int x, int a) {
    for (int Y = y; Y <= H; Y += (Y & -Y)) {
      for (int X = x; X <= W; X += (X & -X)) {
        bit[Y][X] += a;
      }
    }
  }
  // Returns sum of bit[Y][X] for 1 <= Y <= y, 1 <= X <= x, O(logH * logW)
  // y, x: 1-indexed
  int sum(int y, int x) {
    int ret = 0;
    for (int Y = y; Y > 0; Y -= (Y & -Y)) {
      for (int X = x; X > 0; X -= (X & -X)) {
        ret += bit[Y][X];
      }
    }
    return ret;
  }
  // Returns sum of bit[Y][X] for y0 <= Y <= y1, x0 <= X <= x1, O(logH * logW)
  // y0, y1, x0, x1: 1-indexed
  int sum_range(int y0, int x0, int y1, int x1) {
    return sum(y1, x1) - sum(y1, x0 - 1) - sum(y0 - 1, x1) + sum(y0 - 1, x0 - 1);
  }
};

int main() {
  int M, N;;
  cin >> M >> N;
  int K;
  cin >> K;
  binary_indexed_tree_2d bit2d_j(M, N);
  binary_indexed_tree_2d bit2d_o(M, N);
  binary_indexed_tree_2d bit2d_i(M, N);
  for (int y = 0; y < M; y++) {
    string line;
    cin >> line;
    for (int x = 0; x < N; x++) {
      switch (line[x]) {
      case 'J': {
        bit2d_j.add(y + 1, x + 1, 1);
        break;
      }
      case 'O': {
        bit2d_o.add(y + 1, x + 1, 1);
        break;
      }
      case 'I': {
        bit2d_i.add(y + 1, x + 1, 1);
        break;
      }
      }
    }
  }
  for (int k = 0; k < K; k++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << bit2d_j.sum_range(a, b, c, d) << ' '
         << bit2d_o.sum_range(a, b, c, d) << ' '
         << bit2d_i.sum_range(a, b, c, d) << endl;
  }
  return 0;
}
