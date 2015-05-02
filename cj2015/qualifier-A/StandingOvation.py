#!/usr/bin/env python3

def main():
    T = int(input())
    for caseNum in range(1, T+1):
        _, groupSizesStr = input().split()
        groupSizes = [int(d) for d in groupSizesStr]
        friendsNeeded = 0
        standingSoFar = groupSizes[0]
        for shynessLevel, groupSize in enumerate(groupSizes[1:], 1):
            if groupSize > 0 and standingSoFar < shynessLevel:
                friendsNeeded += shynessLevel - standingSoFar
                standingSoFar += shynessLevel - standingSoFar
            standingSoFar += groupSize
        print('Case #{}: {}'.format(caseNum, friendsNeeded))

if __name__ == "__main__":
    main()
