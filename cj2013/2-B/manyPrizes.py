#!/usr/bin/env python

from __future__ import print_function

def highestPossible(N, P):
    if P == 0:
        return -1
    higherNeeded = 0
    roundsPlayed = 0
    while 2 ** (N - roundsPlayed) > P:
        higherNeeded += 2**roundsPlayed
        roundsPlayed += 1
    return 2**N - 1 - higherNeeded

def solveCase():
    N, P = map(int, raw_input().split())
    can = highestPossible(N, P)
    P2 = (2**N - P)
    must = 2**N - 1 - highestPossible(N, P2) - 1
    return (must, can)

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        res = solveCase()
        print('Case #', casenum, ': ', res[0], ' ', res[1], sep='')

if __name__ == '__main__':
    main()


