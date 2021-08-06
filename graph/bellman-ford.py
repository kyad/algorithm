# https://atcoder.jp/contests/abc061/tasks/abc061_d
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_2.cpp
# https://drken1215.hatenablog.com/entry/2019/02/16/075900

INF = 10 ** 9 * 2000 + 1

def bellman_ford(graph, start):
    exist_negative_cycle = False
    N = len(graph)
    dist = [INF] * N
    dist[start] = 0
    in_neg_loop = [False] * N
    for n in range(N * 2):
        update = False
        for v in range(N):
            if dist[v] == INF:
                continue
            for to, weight in graph[v]:
                if dist[to] == INF or (dist[v] + weight < dist[to]):
                    dist[to] = dist[v] + weight
                    update = True
                    if n == N - 1:
                        in_neg_loop[v] = True
        if not update:
            break
        if n == N - 1:
            if update:
                exist_negative_cycle = True
                for v in range(N):
                    if in_neg_loop[v]:
                        dist[v] = -INF
            else:
                break
    return dist, exist_negative_cycle

N, M = map(int, input().split())
graph = [[] for n in range(N)]
for m in range(M):
    a, b, c = map(int, input().split())
    graph[a - 1].append([b - 1, -c])

dist, exist_negative_cycle = bellman_ford(graph, 0)

if dist[N - 1] <= -INF:
    print('inf')
else:
    print(-dist[N - 1])
