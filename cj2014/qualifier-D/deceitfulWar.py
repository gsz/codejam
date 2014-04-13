#!/usr/bin/env python

from __future__ import print_function

def readSolveCase():
    N = int(raw_input())
    naomi = map(float, raw_input().split())
    ken = map(float, raw_input().split())
    naomi.sort()
    ken.sort()
    # good
    honestScore = 0
    naomiIdx = 0
    kenIdx = 0
    while kenIdx < N:
        if ken[kenIdx] < naomi[naomiIdx]:
            honestScore += 1
        else:
            naomiIdx += 1
        kenIdx += 1
    # evil
    evilScore = 0
    naomiIdx = 0
    kenIdxLow = 0
    kenIdxHigh = N-1
    while kenIdxHigh >= kenIdxLow:
        if naomi[naomiIdx] > ken[kenIdxLow]:
            evilScore += 1
            kenIdxLow += 1
        else:
            kenIdxHigh -= 1
        naomiIdx += 1
    evilScore += N - naomiIdx
    return (evilScore, honestScore)

def main():
    T = int(raw_input())
    for t in xrange(1, T+1):
        print('Case #{}: {} {}'.format(t, *readSolveCase()))

if __name__ == "__main__":
    main()
