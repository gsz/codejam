#!/usr/bin/env python

from __future__ import print_function

# horrible mess of special cases
def solveCase(X, Y):
    incDecX = 'EW'
    incDecY = 'NS'
    if X < 0:
        X = -X
        incDecX = ''.join(reversed(incDecX))
    if Y < 0:
        Y = -Y
        incDecY = ''.join(reversed(incDecY))
    sum = 0
    n = 0
    while sum < X + Y:
        n += 1
        sum += n
    while (sum - (X + Y)) % 2 != 0:
        n += 1
        sum += n
    surplus = sum - (X + Y)
    negatives = set()
    yJumps = set()
    x = 0
    i = 0
    while x < X + surplus:
        i += 1
        x += i
    lastXJump = i
    xOverrun = x - (X + surplus)
    if surplus > 0 and xOverrun == surplus / 2 and xOverrun < 3:
        yJumps.update([1,2])
        negatives.add(surplus / 2)
        if xOverrun == 2:
            yJumps.add(3)
    else:
        yJumps.add(xOverrun)
        j = lastXJump
        negated = 0
        while j + negated <= surplus / 2 and j > 0:
            if j not in yJumps:
                negated += j
                negatives.add(j)
            j -= 1
        rest = surplus / 2 - negated
        if rest == 0 or rest not in yJumps:
            negatives.add(rest)
        elif negated > 0 and rest <= j - 2:
            negatives.remove(j+1)
            negatives.update([j, rest+1])
        else:
            negatives.update([rest-1, 1])
    result = ''
    for i in xrange(1, n+1):
        jumps = incDecY if i in yJumps or i > lastXJump else incDecX
        result += jumps[1] if i in negatives else jumps[0]
    return result

def doStuff(stryng):
    x = y = 0
    for (i, l) in enumerate(stryng):
        inc = i + 1
        if l == 'N':
            y += inc
        elif l == 'S':
            y -= inc
        elif l == 'E':
            x += inc
        else:
            x -= inc
    return (x, y)

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        X, Y = map(int, raw_input().split())
        solution = solveCase(X, Y)
        print('Case #', casenum, ': ', solution, sep='')

if __name__ == '__main__':
    main()
