#!/usr/bin/env python

from __future__ import print_function

def readSolveCase():
    n = int(raw_input())
    v1 = map(int, raw_input().split())
    v2 = map(int, raw_input().split())
    v1.sort()
    v2.sort(reverse=True)
    return sum(map(lambda x, y: x*y, v1, v2))

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        print('Case #', casenum, ': ', readSolveCase(), sep='')

if __name__ == '__main__':
    main()
