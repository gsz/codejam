#!/usr/bin/env python3
from collections import defaultdict

def read_solve_case(N):
    numcounts = defaultdict(lambda: 0)
    for n in range(2*N-1):
        for num in map(int, input().split()):
            numcounts[num] += 1
    result = []
    for num in numcounts:
        if numcounts[num] % 2 != 0:
            result.append(num)
    result.sort()
    return ' '.join(map(str, result))

def main():
    T = int(input())
    for ci in range(1, T+1):
        N = int(input())
        print('Case #{}: {}'.format(ci, read_solve_case(N)))

if __name__ == '__main__':
    main()
