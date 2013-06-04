#!/usr/bin/env python

from __future__ import print_function

def readProcessCase():
    S = int(raw_input())
    for _ in xrange(S):
        raw_input() # names are irrelevant
    Q = int(raw_input())
    switches = 0
    queriesSinceSwitch = set()
    for _ in xrange(Q):
        query = raw_input()
        queriesSinceSwitch.add(query)
        if len(queriesSinceSwitch) == S:
            switches += 1
            queriesSinceSwitch.clear()
            queriesSinceSwitch.add(query)
    return switches

def main():
    N = int(raw_input())
    for casenum in xrange(1, N+1):
        print('Case #', casenum, ': ', readProcessCase(), sep='')

if __name__ == '__main__':
    main()
