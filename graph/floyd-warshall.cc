// https://atcoder.jp/contests/abc012/tasks/abc012_4
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_5.cpp

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int INF = 1000 * 299 + 1;
  int N, M;
  cin >> N >> M;
  vector<vector<int> > dist(N, vector<int>(N, INF));
  for (int n = 0; n < N; n++) {
    dist[n][n] = 0;
  }
  for (int m = 0; m < M; m++) {
    int a, b, t;
    cin >> a >> b >> t;
    dist[a - 1][b - 1] = t;
    dist[b - 1][a - 1] = t;
  }
  // Floyd-Warshall algorithm
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  vector<int> temp(N);
  for (int i = 0; i < N; i++) {
    temp.at(i) = *max_element(dist.at(i).begin(), dist.at(i).end());
  }
  cout << *min_element(temp.begin(), temp.end()) << endl;
  return 0;
}
