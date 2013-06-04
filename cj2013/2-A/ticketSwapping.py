#!/usr/bin/env python

from __future__ import print_function

MODULUS = 1000002013

def tripCost(N, o, e):
    return (e - o) * N - (e - o) * (e - o - 1) / 2

def solveCase():
    N, M = map(int, raw_input().split())
    points = {}
    trips = []
    for i in xrange(M):
        o, e, p = map(int, raw_input().split())
        trips.append((o, e, p))
        opt = points.setdefault(o, (0, 0))
        ept = points.setdefault(e, (0, 0))
        points[o] = (opt[0] + p, opt[1])
        points[e] = (ept[0], ept[1] + p)
    travelPlan = sorted(points.iteritems())
    cheaterCosts = simulateCheating(N, travelPlan)
    honestCosts = 0
    for o, e, p in trips:
        honestCosts += (tripCost(N, o, e) * p) % MODULUS
    return (honestCosts - cheaterCosts) % MODULUS

def simulateCheating(N, travelPlan):
    cards = {}
    totalCosts = 0
    for s, (e, l) in travelPlan:
        allCards = []
        if e != 0:
            cards[s] = e
        if l != 0:
            allCards = sorted(cards.iteritems(), reverse=True)
        ci = 0
        while l > 0:
            card = list(allCards[ci])
            oldl = l
            l -= min(card[1], l)
            card[1] -= oldl - l
            allCards[ci] = card
            totalCosts += tripCost(N, card[0], s) * (oldl - l) % MODULUS
            ci += 1
        for origin, num in allCards:
            if cards[origin] == num:
                break
            if num == 0:
                del cards[origin]
            else:
                cards[origin] = num
    return totalCosts

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        print('Case #', casenum, ': ', solveCase(), sep='')

if __name__ == '__main__':
    main()
