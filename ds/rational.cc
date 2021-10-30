// https://atcoder.jp/contests/abc225/tasks/abc225_e

#include <boost/rational.hpp>
#include <iostream>
#include <vector>
using namespace boost;
using namespace std;

typedef rational<long long> rat;

int main() {
  int N;
  cin >> N;
  vector<pair<rat, rat > > fu(N);
  for (int n = 0; n < N; n++) {
    unsigned long long x, y;
    cin >> x >> y;
    rat alpha((y - 1) * (y - 1), (y - 1) * (y - 1) + x * x);
    rat beta(y * y, (x - 1) * (x - 1) + y * y);
    fu.at(n) = make_pair(beta, alpha);
  }
  sort(fu.begin(), fu.end());
  int ans = 0;
  rat maximum = 0;
  for (vector<pair<rat, rat> >::iterator it = fu.begin(); it != fu.end(); it++) {
    rat alpha = it->second;
    rat beta = it->first;
    //cout << "maximum=" << maximum << " " << rational_cast<double>(maximum) << " alpha=" << alpha << " " << rational_cast<double>(alpha) << " beta=" << beta << " " << rational_cast<double>(beta) << endl;
    if (alpha >= maximum) {
      ans++;
      maximum = beta;
    }
  }
  cout << ans << endl;
  return 0;
}
