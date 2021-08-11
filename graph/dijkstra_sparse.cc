// https://atcoder.jp/contests/abc213/tasks/abc213_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_4.cpp
// https://blog.hamayanhamayan.com/entry/2021/08/09/010308

#include <bits/stdc++.h>
using namespace std;

void print_dist(vector<int> dist, int W) {
  const int INF = 1000000000;
  int H = dist.size() / W;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      int idx = y + x * H;
      int d = dist[idx];
      if (d >= INF) {
        printf("inf");
      } else {
        printf("%03d", d);
      }
      if (x == W - 1) {
        putchar('\n');
      } else {
        putchar(' ');
      }
    }
  }
}

int main() {
  const int INF = 1000000000;
  int H, W;
  cin >> H >> W;
  vector<string> S(H);
  for (int h = 0; h < H; h++) {
    cin >> S[h];
  }
  // Dijkstra's algorithm for sparse graph (O|E|log|V|)
  vector<int> dist(H * W, INF);
  dist[0 * W + 0] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push(make_pair(dist[0 * W + 0], 0 * W + 0));
  while (!pq.empty()) {
    int min_dist_idx = pq.top().second;
    int min_dist = pq.top().first;
    pq.pop();
    if (min_dist > dist[min_dist_idx]) {
      continue;
    }
    int y = min_dist_idx / W;
    int x = min_dist_idx % W;
    const int dy[4] = {0, -1, 0, 1};
    const int dx[4] = {-1, 0, 1, 0};
    for (int i = 0; i < 4; i++) {
      int yy = y + dy[i];
      int xx = x + dx[i];
      if (0 <= xx && xx < W && 0 <= yy && yy < H) {
        if (S[yy][xx] == '.') {
          if (dist[yy * W + xx] > min_dist) {
            dist[yy * W + xx] = min_dist;
            pq.push(make_pair(dist[yy * W + xx], yy * W + xx));
          }
        }
      }
    }
    for (int yy = y - 2; yy <= y + 2; yy++) {
      for (int xx = x - 2; xx <= x + 2; xx++) {
        if (0 <= xx && xx < W && 0 <= yy && yy < H && (abs(x - xx) + abs(y - yy) < 4)) {
          if (dist[yy * W + xx] > min_dist + 1) {
            dist[yy * W + xx] = min_dist + 1;
            pq.push(make_pair(dist[yy * W + xx], yy * W + xx));
          }
        }
      }
    }
  }
  cout << dist[(H - 1) * W + (W - 1)] << endl;
  return 0;
}
