# https://atcoder.jp/contests/arc143/tasks/arc143_b
# https://drken1215.hatenablog.com/entry/2018/06/08/210000

MAX = 510000     # n (<= 10^7)
MOD = 998244353  # p (prime, > n)

fac = [0] * MAX  # a! mod p
finv = [0] * MAX # (a!)^{-1} mod p
inv = [0] * MAX  # a^{-1} mod p

# O(n)
def COMinit():
    fac[0] = fac[1] = 1
    finv[0] = finv[1] = 1
    inv[1] = 1
    for i in range(2, MAX):
        fac[i] = fac[i - 1] * i % MOD
        inv[i] = MOD - inv[MOD % i] * (MOD // i) % MOD
        finv[i] = finv[i - 1] * inv[i] % MOD

# nCk mod p, O(1)
def COM(n, k):
    if (n < k):
        return 0
    if (n < 0) or (k < 0):
        return 0
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD

N = int(input())
COMinit()
ans = N ** 2
ans *= COM(N ** 2, 2 * N - 1)
ans %= MOD
ans *= fac[N - 1]
ans %= MOD
ans *= fac[N - 1]
ans %= MOD
ans *= fac[(N - 1)**2]
ans %= MOD
ans = fac[N ** 2] + MOD - ans
ans %= MOD
print(ans)
