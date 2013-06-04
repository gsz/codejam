#!/usr/bin/python

from __future__ import print_function

def checkLine(line):
    if "".join(line).replace('T', 'O') == 'OOOO':
        return 'O won'
    elif "".join(line).replace('T', 'X') == 'XXXX':
        return 'X won'
    
def checkCase(case):
    # horizontal + vertical
    lines = case + zip(*case)
    # diagonals
    lines.append([l[i] for (i, l) in enumerate(case)])
    lines.append([l[-i-1] for (i, l) in enumerate(case)])
    for l in lines:
        if checkLine(l):
            return checkLine(l)
    if '.' not in ''.join((''.join(t) for t in case)):
        return 'Draw'
    return 'Game has not completed'

def readCase():
    return [tuple(raw_input()) for i in xrange(4)]

def main():
    numCases = int(raw_input())
    for i in xrange(1, numCases+1):
        print("Case #", i, ": ", checkCase(readCase()), sep='') 
        raw_input()

if __name__ == '__main__':
    main()
