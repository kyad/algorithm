// https://atcoder.jp/contests/abc007/tasks/abc007_3
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_3.cpp

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int R, C;
  cin >> R >> C;
  int sy, sx;
  cin >> sy >> sx;
  int gy, gx;
  cin >> gy >> gx;
  vector<string> c(R);
  for (int r = 0; r < R; r++) {
    cin >> c.at(r);
  }
  // BFS
  queue<pair<int, int> > todo;
  vector<vector<int> > dist(R, vector<int>(C, -1));
  todo.push(make_pair(sy - 1, sx - 1));
  dist[sy - 1][sx - 1] = 0;
  while (!todo.empty()) {
    int y = todo.front().first;
    int x = todo.front().second;
    todo.pop();
    const int dy[4] = {-1, 0, 1, 0};
    const int dx[4] = {0, -1, 0, 1};
    for (int k = 0; k < 4; k++) {
      int ny = y + dy[k];
      int nx = x + dx[k];
      if (ny < 0 || ny >= R || nx < 0 || nx >= C) {
        continue;
      }
      if (c[ny][nx] == '#') {
        continue;
      }
      if (dist[ny][nx] >= 0) {
        continue;
      }
      dist[ny][nx] = dist[y][x] + 1;
      todo.push(make_pair(ny, nx));
    }
  }
  cout << dist[gy - 1][gx - 1] << endl;
}
