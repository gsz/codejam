#!/usr/bin/env python

from __future__ import print_function

class HornSatSolver(object):
    @classmethod
    def readInstance(cls):
        obj = HornSatSolver()
        N = int(raw_input())
        M = int(raw_input())
        obj.varQueue = []
        obj.valuation = [False] * (N + 1)
        obj.clausesWith = [[] for n in xrange(N+1)]
        for m in xrange(M):
            l = map(int, raw_input().split())
            clause = [None, 0]
            for i in xrange(1, l[0]*2 + 1, 2):
                if l[i+1]:
                    clause[0] = l[i]
                else:
                    obj.clausesWith[l[i]].append(clause)
                    clause[1] += 1
            if clause[1] == 0:
                obj.varQueue.append(clause[0])
        return obj

    def solve(self):
        while self.varQueue:
            v = self.varQueue.pop()
            if self.valuation[v]:
                continue
            self.valuation[v] = 1
            for c in self.clausesWith[v]:
                c[1] -= 1
                if c[1] == 0:
                    if c[0]:
                        self.varQueue.append(c[0])
                    else:
                        return 'IMPOSSIBLE'
        return self.valuation[1:]

def main():
    T = int(raw_input())
    for casenum in xrange(1, T+1):
        case = HornSatSolver.readInstance()
        solution = case.solve()
        if solution != 'IMPOSSIBLE':
            solution = ' '.join(map(lambda b: str(int(b)), solution))
        print('Case #', casenum, ': ', solution, sep='')

if __name__ == '__main__':
    main()
