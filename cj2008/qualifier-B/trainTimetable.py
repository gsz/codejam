#!/usr/bin/env python 

from __future__ import print_function

def readSolveCase():
    T = int(raw_input())
    NA, NB = map(int, raw_input().split())
    events = []
    for iA in xrange(NA):
        depart, arrive = (int(h)*60 + int(m) for (h, m) in 
                (hm.split(':') for hm in raw_input().split()))
        arrive += T
        events.extend(((depart, 'departA'), (arrive, 'arriveB')))
    for iB in xrange(NB):
        depart, arrive = (int(h)*60 + int(m) for (h, m) in 
                (hm.split(':') for hm in raw_input().split()))
        arrive += T
        events.extend(((depart, 'departB'), (arrive, 'arriveA')))
    events.sort()
    aTrains = bTrains = minATrains = minBTrains = 0
    for evTime, evType in events:
        if evType == 'departA':
            aTrains -= 1
            minATrains = min(minATrains, aTrains)
        elif evType == 'departB':
            bTrains -= 1
            minBTrains = min(minBTrains, bTrains)
        elif evType == 'arriveA':
            aTrains += 1
        else:
            bTrains += 1
    return (-minATrains, -minBTrains)

def main():
    N = int(raw_input())
    for casenum in xrange(1, N+1):
        print('Case #', casenum, ': ', ' '.join(map(str, readSolveCase())), 
                sep='')

if __name__ == '__main__':
    main()
