# https://atcoder.jp/contests/abc213/tasks/abc213_c

# Return 0-order compressed list whose size is same as A
def compress(A):
    m = {value: i for i, value in enumerate(sorted(list(set(A))))}
    return [m[A[i]] for i in range(len(A))]

H, W, N = map(int, input().split())
A = [-1] * N
B = [-1] * N
for n in range(N):
    A[n], B[n] = map(int, input().split())
C = compress(A)
D = compress(B)
for n in range(N):
    print(C[n] + 1, D[n] + 1)
