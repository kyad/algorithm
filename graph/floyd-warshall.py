# https://atcoder.jp/contests/abc143/tasks/abc143_e
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_5.cpp
# Python3=TLE, PyPy3=AC

INF = 10 ** 9 * 300 + 1

N, M, L = map(int, input().split())
dp = [[INF] * N for n in range(N)]
for n in range(N):
    dp[n][n] = 0

for m in range(M):
    A, B, C = map(int, input().split())
    dp[A - 1][B - 1] = C
    dp[B - 1][A - 1] = C

# Floyd-Warshall algorithm
for k in range(N):
    for i in range(N):
        for j in range(N):
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
exist_negative_cycle = False
for n in range(N):
    if dp[n][n] < 0:
        exist_negative_cycle = True

dp2 = [[INF] * N for n in range(N)]
for i in range(N):
    for j in range(N):
        if i == j:
            dp2[i][j] = 0
        elif dp[i][j] <= L:
            dp2[i][j] = 1

# Floyd-Warshall algorithm
for k in range(N):
    for i in range(N):
        for j in range(N):
            dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k][j])

Q = int(input())
for q in range(Q):
    s, t = map(int, input().split())
    print(-1 if dp2[s - 1][t - 1] == INF else (dp2[s - 1][t - 1] - 1))
