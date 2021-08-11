# https://atcoder.jp/contests/abc213/tasks/abc213_c

H, W, N = map(int, input().split())
h_exist = set()
w_exist = set()
A = [0] * N
B = [0] * N
for n in range(N):
    a, b = map(int, input().split())
    h_exist.add(a - 1)
    w_exist.add(b - 1)
    A[n] = a - 1
    B[n] = b - 1
h_exist = list(h_exist)
w_exist = list(w_exist)
h_exist.sort()
w_exist.sort()
h_count = 0
h_convert = {}
for h in h_exist:
    h_convert[h] = h_count
    h_count += 1
w_count = 0
w_convert = {}
for w in w_exist:
    w_convert[w] = w_count
    w_count += 1
for n in range(N):
    print(h_convert[A[n]] + 1, w_convert[B[n]] + 1)
