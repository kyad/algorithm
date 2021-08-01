# https://atcoder.jp/contests/abc211/tasks/abc211_d
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_3.cpp

import queue

N, M = map(int, input().split())
graph = [[] for i in range(N)]
for i in range(M):
    A, B = map(int, input().split())
    graph[A - 1].append(B - 1)
    graph[B - 1].append(A - 1)

todo = queue.Queue()
dist = [None] * N
count = [0] * N
start = 0  # start node
todo.put(start)
dist[start] = 0
count[start] = 1
while not todo.empty():
    v = todo.get()
    for x in graph[v]:
        if dist[x] is None:
            dist[x] = dist[v] + 1
            todo.put(x)
        if dist[x] == dist[v] + 1:
            count[x] += count[v]
            count[x] %= (10 ** 9 + 7)  # MOD
             
print(count[N - 1])
