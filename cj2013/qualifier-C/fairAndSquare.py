#!/usr/bin/python

from __future__ import print_function
import decimal
from decimal import Decimal

_factorialTable = [1]
for n in xrange(1,51):
    _factorialTable.append(_factorialTable[-1] * n)

def factorial(n):
    return _factorialTable[n]

def combinations(n, k):
    if k > n:
        return 0
    else:
        return factorial(n) / factorial(n-k) / factorial(k)
       
# number of palindromic square roots of palindromes of a given length
def _fairRootsOfLength(l):
    if l == 1:
        return 3
    else:
        num = 0
        # form 1: 1___1 + up to 7 ones inside
        for k in xrange(4): 
            num += combinations(l / 2 - 1, k) * (1 + l % 2)
        # form 2: 1___1 + 2 in the middle + optional 2 ones
        if l % 2:
            num += l / 2
        # form 3: 2___2 + optional 1 in the possibly existing middle 
        num += 1 + l % 2
    return num

_fairRootsOfLengthTable = [0]
for l in xrange(1,52):
    _fairRootsOfLengthTable.append(_fairRootsOfLength(l))

def fairRootsOfLength(l):
    return _fairRootsOfLengthTable[l]

# number of palindromic square roots of palindromes greater than n and of
# the same length
def fairRootsAbove(n):
    decimal = str(n)
    l = len(decimal)
    if l == 1:
        return max(0, 3 - n)
    num = 0
    num += _fairRootsAboveForm1(n, decimal, l)
    num += _fairRootsAboveForm2(n, decimal, l)
    num += _fairRootsAboveForm3(n, decimal, l)
    return num

def _fairRootsAboveForm1(n, decimal, l):
    result = 0
    if decimal[0] != '1':
        return 0
    lastNonzero = 0
    assignedOnes = 0
    for pos in xrange(1, l/2+1):
        if assignedOnes == 3 or decimal[pos-1] not in ('0', '1'):
             break
        if decimal[pos] != '0' or pos == l/2:
            assignedOnes += 1
            for pos2 in xrange(lastNonzero + 1, pos):
                for k in xrange(0, 4 - assignedOnes):
                    kcombs = combinations(l / 2 - pos2 - 1, k)
                    result += kcombs * (1 + l % 2)
            lastNonzero = pos
    if (set(decimal[:(l+1)/2]) <= set(['0', '1']) 
            and decimal[:l/2].count('1') <= 4):
        minAbove = decimal[:l/2] + decimal[l/2:(l+1)/2] + decimal[l/2-1::-1]
        if int(minAbove) > n:
            result += 1
        if l % 2 and decimal[l/2] == '0':
            if int(decimal[:l/2] + '1' + decimal[l/2-1::-1]) > n:
                result += 1
    return result

def _fairRootsAboveForm2(n, decimal, l):
    if decimal[0] != '1' or not l % 2:
        return 0
    result = 0
    for i in xrange(1, l/2 + 1):
        if decimal[i] != '0' or i == l/2:
            secondNonzero = i
            break
    result += secondNonzero - 1
    if decimal[secondNonzero] != '1' and secondNonzero != l/2:
        return result
    if set(decimal[secondNonzero+1:l/2]) <= set('0'):
        if decimal[l/2] in '01':
            result += 1
        elif decimal[l/2] == '2':
            if int(decimal[:l/2+1] + decimal[l/2-1::-1]) > n:
                result += 1
    return result

def _fairRootsAboveForm3(n, decimal, l):
    result = 0
    if int('2' + '0' * (l-2) + '2') > n:
        result +=1
    if l % 2 and int('2' + '0' * (l/2 - 1) + '1' + '0' * (l/2 - 1) + '2') > n:
        result += 1
    return result

# number of palindromic square roots of palindromes lesser than n and of
# the same length
def fairRootsBelow(n):
    l = len(str(n))
    if n == 10**(l-1):
        return 0
    else:
        return fairRootsOfLength(l) - fairRootsAbove(n-1)

def fairRootsInRange(a, b):
    la = len(str(a))
    lb = len(str(b))
    result = fairRootsOfLength(la) - fairRootsBelow(a)
    for l in xrange(la + 1, lb + 1):
        result += fairRootsOfLength(l)
    result -= fairRootsAbove(b)
    return result

def main():
    decimal.getcontext().prec=101
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        A, B = map(int, raw_input().split())
        sqrtA = int(Decimal(A).sqrt().to_integral_value(decimal.ROUND_UP))
        sqrtB = int(Decimal(B).sqrt().to_integral_value(decimal.ROUND_DOWN))
        fairAndSquares = fairRootsInRange(sqrtA, sqrtB)
        print('Case #', casenum, ': ', fairAndSquares, sep='')

if __name__ == '__main__':
    main()
