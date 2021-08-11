// https://atcoder.jp/contests/arc005/tasks/arc005_3
// https://drken1215.hatenablog.com/entry/2021/07/30/024800
// https://betrue12.hateblo.jp/entry/2018/12/08/000020

#include <iostream>
#include <deque>
#include <string>
#include <vector>
using namespace std;

int main() {
  const int INF = 500 * 500 + 1;
  int H, W;
  cin >> H >> W;
  vector<string> c(H);
  for (int h = 0; h < H; h++) {
    cin >> c[h];
  }
  int start_y, start_x;
  int goal_y, goal_x;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (c[y][x] == 's') {
        start_y = y;
        start_x = x;
      } else if (c[y][x] == 'g') {
        goal_y = y;
        goal_x = x;
      }
    }
  }
  // 01-BFS
  vector<int> dist(H * W, INF);
  deque<int> dq;
  dist[start_y * W + start_x] = 0;
  dq.push_back(start_y * W + start_x);
  while (!dq.empty()) {
    int min_dist_idx = dq.front();
    dq.pop_front();
    int y = min_dist_idx / W;
    int x = min_dist_idx % W;
    const int dy[] = {0, -1, 0, 1};
    const int dx[] = {-1, 0, 1, 0};
    for (int i = 0; i < 4; i++) {
      int yy = y + dy[i];
      int xx = x + dx[i];
      if (0 <= yy && yy < H && 0 <= xx && xx < W) {
        if (c[yy][xx] == '#') { // cost=1
          if (dist[yy * W + xx] > dist[min_dist_idx] + 1) {
            dist[yy * W + xx] = dist[min_dist_idx] + 1;
            dq.push_back(yy * W + xx);
          }
        } else { // cost=0
          if (dist[yy * W + xx] > dist[min_dist_idx]) {
            dist[yy * W + xx] = dist[min_dist_idx];
            dq.push_front(yy * W + xx);
          }
        }
      }
    }
  }
  cout << (dist[goal_y * W + goal_x] <= 2 ? "YES" : "NO") << endl;
  return 0;
}
