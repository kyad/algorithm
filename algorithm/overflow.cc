#include <algorithm>
#include <iostream>
using namespace std;

// 計算結果がオーバーフローする(Mより大きくなる)ならtrueを返す
#include <limits>
bool overflow_add(long long a, long long b, long long M = numeric_limits<long long>::max()) { return M - a < b; }
bool overflow_mul(long long a, long long b, long long M = numeric_limits<long long>::max()) { return (a != 0) && (M / a < b); }
bool overflow_mul3(long long a, long long b, long long c, long long M = numeric_limits<long long>::max()) { return overflow_mul(a, b, M) || overflow_mul(a * b, c, M); }

int main() {
  long long A, B;
  cin >> A >> B;
  long long g = __gcd(A, B);
  long long c = A / g;
  const long long INF = 1000000000000000000;
  if (overflow_mul(B, c, INF)) {
    cout << "Large" << endl;
  } else {
    cout << c * B << endl;
  }
  return 0;
}
