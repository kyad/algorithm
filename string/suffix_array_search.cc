// https://atcoder.github.io/ac-library/document_ja/string.html
// https://niuez.hatenablog.com/entry/2019/12/16/203739
// Not verified

#include <iostream>
#include <vector>
using namespace std;
#include <atcoder/string>
using namespace atcoder;

/**
 * Suffix arrayを使って文字列Sの中にTがあるかどうかを判定する。
 * 計算量はO(|T|log|S|)
 *
 * \param[in] S 検索される文字列
 * \param[in] sa Sのsuffix array (atcoder::suffix_array(S), O(|S|))
 * \param[in] T 検索する文字列
 * \return int 見つかれば検索された位置のうち1つ(>=0)、見つからなければ-1
 */
int suffix_array_search(const string &S, const vector<int> &sa, const string &T) {
  int left = 0;
  int right = sa.size();
  while (right - left > 1) {
    int mid = (left + right) / 2;
    if (S.substr(sa[mid], T.size()) <= T) {
      left = mid;
    } else {
      right = mid;
    }
  }
  if (s.substr(sa[left], T.size()) == T) {
    return sa[left];
  } else {
    return -1;
  }
}
