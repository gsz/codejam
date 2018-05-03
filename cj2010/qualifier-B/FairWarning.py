#!/usr/bin/env python3
def gcd(n,m):
    while m > 0:
        n, m = m, n % m
    return n

C = int(input())
for casenum in range(1, C+1):
    N_t = [int(w) for w in input().split()]
    t = N_t[1:]
    diff_gcd = 0
    for i in range(1, len(t)):
        diff_gcd = gcd(abs(t[i] - t[i-1]), diff_gcd)
    y = (diff_gcd - t[0] % diff_gcd) % diff_gcd
    print("Case #{}: {}".format(casenum, y))
