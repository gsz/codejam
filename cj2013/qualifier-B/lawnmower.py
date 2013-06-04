#!/usr/bin/python
from __future__ import print_function

def readCheckCase():
    N, M = map(int, raw_input().split())
    rowMaxima = []
    columnMaxima = [0 for i in xrange(M)]
    targetLawn = []
    for n in xrange(N):
        row = map(int, raw_input().split())
        rowMaxima.append(max(row))
        columnMaxima = map(max, columnMaxima, row)
        targetLawn.append(row)
    for n in xrange(N):
        for m in xrange(M):
            if (targetLawn[n][m] != rowMaxima[n]  
                    and targetLawn[n][m] != columnMaxima[m]):
                return False
    return True

def main():
    numCases = int(raw_input())
    for i in xrange(numCases):
        print("Case #", i+1, ": ", 'YES' if readCheckCase() else 'NO', sep='')

if __name__ == '__main__':
    main()
