#!/usr/bin/python

from __future__ import print_function

def readSolveCase():
    E, R, N = map(int, raw_input().split())
    if R > E:
        R = E
    v = map(int, raw_input().split())
    e = E
    totalVal = 0
    newIdx = actIdx = 0
    while actIdx < N:
        # number of steps until regeneration overflows
        waitHorizon = (E - e) / R + 1
        for i in xrange(actIdx + 1, min(actIdx + waitHorizon, N)):
            if v[i] > v[actIdx]:
                e += (i - actIdx) * R
                assert e <= E
                newIdx = i
                break
        if newIdx > actIdx:
            actIdx = newIdx
            continue
        # number of steps until regeneration overflows by more than current e
        spendHorizon = E / R + 1
        for i in xrange(actIdx + waitHorizon, min(actIdx + spendHorizon, N)):
            if v[i] > v[actIdx]:
                assert (e + (i - actIdx) * R - E) > 0
                assert (e + (i - actIdx) * R - E) <= e
                totalVal += (e + (i - actIdx) * R - E) * v[actIdx]
                newIdx = i
                e = E
                break
        if newIdx > actIdx:
            actIdx = newIdx
            continue
        totalVal += e * v[actIdx]
        actIdx += 1
        e = R
    return totalVal

def main():
    T = int(raw_input())
    for caseNum in xrange(1, T+1):
        print("Case #", caseNum, ": ", readSolveCase(), sep='')

if __name__ == '__main__':
    main()


