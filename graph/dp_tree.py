# https://atcoder.jp/contests/abc036/tasks/abc036_d
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_9.cpp

import sys

def main():
    MOD = 10 ** 9 + 7
    N = int(sys.stdin.readline())
    tree = [[] for i in range(N)]
    for n in range(N - 1):
        a, b = map(int, sys.stdin.readline().split())
        tree[a - 1].append(b - 1)
        tree[b - 1].append(a - 1)
    # DP for tree
    dp_white = [-1] * N
    dp_black = [-1] * N
    def dfs(tree, v, parent):
        dp_white[v] = 1
        dp_black[v] = 1
        for child in tree[v]:
            if child == parent:
                continue
            dfs(tree, child, v)
            dp_white[v] *= (dp_white[child] + dp_black[child])
            dp_white[v] %= MOD
            dp_black[v] *= dp_white[child]
            dp_black[v] %= MOD
    dfs(tree, 0, -1)
    print((dp_white[0] + dp_black[0]) % MOD)

if __name__ == '__main__':
    main()
