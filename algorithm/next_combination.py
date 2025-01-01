# https://atcoder.jp/contests/abc386/tasks/abc386_e
# https://atcoder.jp/contests/abc386/editorial/11697

# import pypyjit
import itertools
import sys

# pypyjit.set_param("max_unroll_recursion=-1")
sys.set_int_max_str_digits(0)
sys.setrecursionlimit(10**6)


def main():
    N, K = map(int, input().split())
    A = list(map(int, input().split()))
    ans = 0
    if K <= N - K:  # Kが大きい場合は時間がかかるのでN-Kとして処理するために場合分けする
        for x in itertools.combinations(A, K):
            now = 0
            for a in x:
                now ^= a
            ans = max(ans, now)
    else:
        all_sum = 0
        for a in A:
            all_sum ^= a
        for x in itertools.combinations(A, N - K):
            now = all_sum
            for a in x:
                now ^= a
            ans = max(ans, now)
    print(ans)


if __name__ == "__main__":
    main()
