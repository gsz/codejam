#!/usr/bin/env python

from __future__ import print_function

from heapq import *
from collections import deque

class Tribe(object):
    def __init__(self, d, n, w, e, s, delta_d, delta_p, delta_s):
        self.delta_d = delta_d
        self.delta_p = delta_p
        self.delta_s = delta_s
        self.nextAttack = d
        self.attacksLeft = n
        self.strength = s
        self.w = w
        self.e = e

    def attack(self):
        assert self.attacksLeft > 0
        retVal = (self.w, self.e, self.strength)
        self.e += self.delta_p
        self.w += self.delta_p
        self.strength += self.delta_s
        self.attacksLeft -= 1
        if self.attacksLeft > 0:
            self.nextAttack += self.delta_d
        else:
            self.nextAttack = None
        return retVal

class Wall(object):
    def __init__(self, endpoints):
        self.tree = self.buildTree(endpoints)

    class Node(object):
        def __init__(self, w, e, mid, left, right):
            self.w = w
            self.e = e
            self.mid = mid
            self.left = left
            self.right = right
            self.minHeight = 0

    @classmethod
    def buildTree(cls, endpoints):
        if len(endpoints) == 2:
            return Wall.Node(endpoints[0], endpoints[1], None, None, None)
        w, mid, e = endpoints[0], endpoints[len(endpoints)/2], endpoints[-1]
        left = cls.buildTree(endpoints[:len(endpoints)/2 + 1])
        right = cls.buildTree(endpoints[len(endpoints)/2:])
        return Wall.Node(w, e, mid, left, right)

    def attackSuccessful(self, (w, e, s)):
        return self.treeWalk(w, e, s, self.tree, 0, build = False)

    def buildWall(self, (w, e, s)):
        self.treeWalk(w, e, s, self.tree, 0, build = True)

    def treeWalk(self, w, e, s, node, maxMin, build = False):
        if w >= e:
            return False
        maxMin = max(node.minHeight, maxMin)
        if maxMin >= s:
            return False
        if w == node.w and e == node.e:
            if build:
                node.minHeight = s
            return True
        if build:
            self.treeWalk(w, min(e, node.mid), s, node.left, maxMin, build)
            self.treeWalk(max(w, node.mid), e, s, node.right, maxMin, build)
            if (node.left.minHeight > node.minHeight 
                    and node.right.minHeight > node.minHeight):
                node.minHeight = min(node.left.minHeight, node.right.minHeight)
            return
        return (self.treeWalk(w, min(e, node.mid), s, node.left, maxMin)
                or self.treeWalk(max(w, node.mid), e, s, node.right, maxMin))

    def ppWalk(self, node):
        rootStr = str((node.w, node.mid, node.e, node.minHeight))
        if node.mid:
            (llen, left) = self.ppWalk(node.left)
            (rlen, right) = self.ppWalk(node.right)
            totallen = max(len(rootStr), llen + rlen + 3)
            l1 = ' ' * ((totallen - len(rootStr)) / 2)
            l1 += rootStr + ' ' * ((totallen - len(rootStr) + 1) / 2)
            l2 = ' ' * ((totallen - rlen - 3) / 2)
            l2 += '+' + '-' * (totallen / 2 - len(l2) - 1) + '+'
            l2 += '-' * ((totallen + 1) / 2 - (totallen - llen - 3) / 2 - 1)
            l2 += '+' + ' ' * (totallen - len(l2) - 1)
            lmargin = ' ' * ((totallen - llen - rlen - 3) / 2)
            rmargin = ' ' * ((totallen - llen - rlen - 3 + 1) / 2)
            lines = [l1, l2]
            lines.extend(map(lambda s1, s2: lmargin + (s1 or '') + '   ' + 
                (s2 or '') + rmargin, left, right))
            return (totallen, lines)
        else:
            return(len(rootStr), [rootStr])

    def prettyPrintTree(self):
        map(print, self.ppWalk(self.tree)[1])

    def printTree(self, node, indent=''):
        if not node:
            print(indent, '-')
            return
        print(indent, 'Node:', node.w, node.mid, node.e, node.minHeight)
        print(indent, 'Left:')
        self.printTree(node.left, indent+' ')
        print(indent, 'Right:')
        self.printTree(node.right, indent+' ')

def readTribes(N):
    tribes = []
    for i in xrange(N):
        di, ni, wi, ei, si, delta_di, delta_pi, delta_si = (
                map(int, raw_input().split()))
        tribes.append(Tribe(di, ni, wi, ei, si, delta_di, delta_pi, delta_si))
    return tribes

def genAttacks(tribes):
    attacks = []
    for t in tribes:
        while t.nextAttack != None:
            day = t.nextAttack
            attacks.append((day, t.attack()))
    attacks.sort(key = lambda t: t[0])
    return attacks

def readSolveCase():
    N = int(raw_input())
    tribes = readTribes(N)
    attacks = genAttacks(tribes)
    endpoints = sorted({a[1][i] for a in attacks for i in (0,1)})
    wall = Wall(endpoints)
    successfulAttacks = 0
    i = 0
    while i < len(attacks):
        day = attacks[i][0]
        dayAttacks = []
        while i < len(attacks) and attacks[i][0] == day:
            d, a = attacks[i]
            if wall.attackSuccessful(a):
                successfulAttacks += 1
                dayAttacks.append(a)
            i += 1
        for a in dayAttacks:
            wall.buildWall(a)
    return successfulAttacks

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        print('Case #', casenum, ': ', readSolveCase(), sep='')

if __name__ == '__main__':
    main()
