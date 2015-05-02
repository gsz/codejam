#!/usr/bin/env python3

from functools import reduce

I = 2
J = 3
K = 4

encodeQuaternion = {'i' : 2, 'j' : 3, 'k' : 4}

_mulTable = [[0,  0,  0,  0,  0]
            ,[0,  1,  2,  3,  4]
            ,[0,  2, -1,  4, -3]
            ,[0,  3, -4, -1,  2]
            ,[0,  4,  3, -2, -1]
            ,]

def quatMul(a, b):
    sgnA = 1 - 2 * (a < 0)
    sgnB = 1 - 2 * (b < 0)
    return _mulTable[abs(a)][abs(b)] * sgnA * sgnB

def genMulTable():
    table = [[0, 0, 0, 0, 0]]
    for rowIdx in (1, I, J, K):
        row = [0]
        for colIdx in (1, I, J, K):
            if rowIdx == 1:
                val = colIdx
            elif colIdx == 1:
                val = rowIdx
            elif rowIdx == colIdx:
                val = -1
            elif (rowIdx - 2 + 1) % 3 == (colIdx - 2) % 3:
                val = (rowIdx - 2 + 2) % 3 + 2
            else:
                val = -((rowIdx - 2 - 2) % 3 + 2)
            row.append(val)
        table.append(row)
    return table

# Sanity check
assert _mulTable == genMulTable()

def solveCase(L, X, quats):
    segmentVal = reduce(quatMul, quats)
    finalVal = 1
    for i in range(X % 4):
        finalVal = quatMul(finalVal, segmentVal)
    if finalVal != -1:
        return False
    iters = 0
    currentVal = 1
    while iters < min(L * 4, L * X) and currentVal != I:
        currentVal = quatMul(currentVal, quats[iters % L])
        iters += 1
    if currentVal != I:
        return False
    iters2 = 0
    currentVal = 1
    while iters2 < L * 4 and iters + iters2 < L * X and currentVal != J:
        currentVal = quatMul(currentVal, quats[(iters + iters2) % L])
        iters2 += 1
    if currentVal != J:
        return False
    return True

def main():
    T = int(input())
    for caseNum in range(1, T+1):
        L, X = map(int, input().split())
        quats = [encodeQuaternion[q] for q in input()]
        print('Case #{}: {}'.format(caseNum, 'YES' if solveCase(L, X, quats)
                                             else 'NO'))

if __name__ == "__main__":
    main()
