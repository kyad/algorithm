// https://atcoder.jp/contests/joi2012yo/tasks/joi2012yo_e

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  int W, H;
  cin >> W >> H;
  vector<vector<int> > board(H, vector<int>(W));
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      cin >> board[y][x];
    }
  }
  vector<vector<bool> > is_outside(H, vector<bool>(W, false));
  vector<pair<int, int> > start;
  for (int x = 0; x < W; x++) {
    start.push_back(make_pair(0, x));
    start.push_back(make_pair(H - 1, x));
  }
  for (int y = 1; y < H - 1; y++) {
    start.push_back(make_pair(y, 0));
    start.push_back(make_pair(y, W - 1));
  }
  // y == even: dy[0][], dx[0][]
  // y == odd : dy[1][], dx[1][]
  const int dy[2][6] = { {-1, -1, 0, 1, 1,  0}, {-1, 0, 1,  1,  0, -1} };
  const int dx[2][6] = { { 0,  1, 1, 1, 0, -1}, { 0, 1, 0, -1, -1, -1} };
  for (size_t s = 0; s < start.size(); s++) {
    int sy = start[s].first;
    int sx = start[s].second;
    if (board[sy][sx]) {
      continue;
    }
    // DFS
    vector<vector<bool> > seen(H, vector<bool>(W, false));
    stack<pair<int, int> > todo;
    todo.push(make_pair(sy, sx));
    while (!todo.empty()) {
      int y = todo.top().first;
      int x = todo.top().second;
      seen[y][x] = true;
      is_outside[y][x] = true;
      todo.pop();
      for (int k = 0; k < 6; k++) {
        int ny = y + dy[y % 2][k];
        int nx = x + dx[y % 2][k];
        if (ny < 0 || ny >= H || nx < 0 || nx >= W || board[ny][nx]) {
          continue;
        }
        if (seen[ny][nx]) {
          continue;
        }
        todo.push(make_pair(ny, nx));
      }
    }
  }
  int ans = 0;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      for (int k = 0; k < 6; k++) {
        int ny = y + dy[y % 2][k];
        int nx = x + dx[y % 2][k];
        if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
          if (!is_outside[y][x]) {
            ans++;
          }
        } else {
          if (is_outside[y][x] && (!is_outside[ny][nx])) {
            ans++;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
