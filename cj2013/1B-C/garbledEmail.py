#!/usr/bin/env python

from __future__ import print_function

FLAG = 26
def buildPrefixTree(dictfile):
    f = file(dictfile, 'r')
    prefixTree = [None] * 27
    for word in f:
        curSubtree = prefixTree
        for letter in word.strip():
            lcode = ord(letter) - ord('a')
            if not curSubtree[lcode]:
                curSubtree[lcode] = [None] * 27
            curSubtree = curSubtree[lcode]
        curSubtree[FLAG] = True
    f.close()
    return prefixTree

def solveCase(S, prefixTree):
    INFINITY = (len(S) + 4) / 5
    S = S + 'z' # guard
    minChanges = [[INFINITY] * 5 for i in xrange(len(S))]
    minChanges[-1] = [INFINITY] * 4 + [0] # guard
    for i in xrange(len(S) - 1, -1, -1):
        traversePrefixTree(S, i, minChanges, prefixTree)
    return min(minChanges[0])

def traversePrefixTree(S, i, minChanges, prefixTree, 
        j = 0, firstChange = None, lastChange=-5, changes=0):
    while prefixTree and i + j < len(S):
        letCode = ord(S[i + j]) - ord('a')
        if i + j - lastChange >= 5:
            for l in xrange(26):
                if l == letCode:
                    continue
                traversePrefixTree(S, i, minChanges, prefixTree[l], j = j + 1, 
                        firstChange = (
                            firstChange if firstChange != None else i + j),
                        lastChange = i + j, changes = changes + 1)
        if prefixTree[FLAG]:
            minChangeOffs = max(0, lastChange + 5 - (i + j))
            for nextChangeOffs in xrange(max(0, lastChange + 5 - (i + j)), 5):
                if firstChange:
                    firstChangeOffs = min(firstChange - i, 4)
                else:
                    firstChangeOffs = min(4, j + nextChangeOffs)
                minChanges[i][firstChangeOffs] = min(
                        minChanges[i][firstChangeOffs],
                        minChanges[i+j][nextChangeOffs] + changes)
        prefixTree = prefixTree[letCode]
        j += 1

def processFile(inp, out, prefixTree):
    fi = file(inp, 'r')
    fo = file(out, 'w')
    T = int(fi.readline())
    for casenum in xrange(1, T+1):
        case = fi.readline().strip()
        fo.write('Case #' + str(casenum) + ': ' + str(solveCase(case, prefixTree)) + '\n')
    fo.close()
    fi.close()
