# https://atcoder.jp/contests/abc150/tasks/abc150_d

import math

def my_lcm(a, b):
    return (a * b) // math.gcd(a, b)

N, M = map(int, input().split())
a = list(map(int, input().split()))
b = [0] * N
for n in range(N):
    b[n] = a[n] // 2
L = 1
for n in range(N):
    L = my_lcm(L, b[n])
    if L > M:
        print(0)
        exit(0)
for n in range(N):
    if (L // b[n]) % 2 == 0:
        print(0)
        exit(0)
U = (M - L) // (2 * L)
print(U + 1)
