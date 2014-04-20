#!/usr/bin/env python

from __future__ import print_function
import collections
import math
import operator

class Vector2(collections.namedtuple('vec2', 'x y')):
    def __neg__(self):
        return Vector2(-self.x, -self.y)

    def __add__(self, other):
        return Vector2(*map(operator.add, self, other))

    def __sub__(self, other):
        return Vector2(*map(operator.sub, self, other))

    def dotProduct(self, other):
        return sum(map(operator.mul, self, other))

    def __mul__(self, other):
        return Vector2(*(x * other for x in self))

    def crossProduct(self, other):
        return self.x * other.y - self.y * other.x

    def __radd__(self, other):
        return self.__add__(other)

    def __rsub__(self, other):
        return self.__sub__(other)

    def __rmul__(self, other):
        return self.__mul__(other)

    def __abs__(self):
        return math.sqrt(self.x**2 + self.y**2)

# Area of (convex) slice of circle centered at (0, 0) of radiurs r, between
# vectors v1 and v2
def sliceArea(r, v1, v2):
    return r**2 * math.acos(v1.dotProduct(v2) / abs(v1) / abs(v2)) / 2

def triangleArea(p1, p2, p3):
    return abs((p3 - p1).crossProduct(p2 - p1)) / 2

def segmentCircleIntersect(p1, p2, r):
    dot = (p2 - p1).dotProduct(p1) 
    squareLen = (p2 - p1).dotProduct(p2 - p1)
    delta = 4 * dot**2 - 4 * squareLen * (p1.dotProduct(p1) - r**2)
    if delta < 0:
        return None
    x1 = (-2 * dot + math.sqrt(delta)) / (2 * squareLen)
    x2 = (-2 * dot - math.sqrt(delta)) / (2 * squareLen)
    if 1 >= x1 >= 0:
        return p1 * (1 - x1) + p2 * x1
    if 1 >= x2 >= 0:
        return p1 * (1 - x2) + p2 * x2

def polygonArea(poly):
    poly = list(poly)[:]
    area = 0
    while len(poly) >= 3:
        area += triangleArea(*poly[-3:])
        del poly[-2]
    return area

# Area of overlap of a rectangle in the NE quadrant and a circle with center at
# (0, 0) and radius r
def rectOverlapArea(swCorner, width, height, r):
    assert min(swCorner.x, swCorner.y, width, height) >= 0
    rectPoints = [swCorner]
    rectPoints.append(rectPoints[-1] + Vector2(0.0, height))
    rectPoints.append(rectPoints[-1] + Vector2(width, 0.0))
    rectPoints.append(rectPoints[-1] + Vector2(0.0, -height))
    intersections = [] 
    points = []
    for i in xrange(len(rectPoints)):
        if len(intersections) % 2 == 0:
            points.append(rectPoints[i])
        intersect = segmentCircleIntersect(rectPoints[i], 
                                           rectPoints[(i+1) % len(rectPoints)], 
                                           r)
        if intersect:
            points.append(intersect)
            intersections.append(intersect)
    if len(intersections) < 2:
        return width * height
    else:
        area = sliceArea(r, *intersections)
        area -= triangleArea(Vector2(0.0, 0.0), *intersections)
        area += polygonArea(points)
        return area

def gapArea(innerR, r, g):
    swCorner = Vector2(r, r)
    skip = 2 * r + g
    area = 0
    while abs(swCorner) < innerR:
        maxXSquare = innerR**2 - (swCorner.y + g)**2
        if maxXSquare >= 0:
            maxX = math.sqrt(maxXSquare)
            wholeGaps = math.floor(maxX / skip)
            area += wholeGaps * g**2
        else:
            wholeGaps = 0
        swCorner2 = swCorner + Vector2(wholeGaps * skip, 0.0)
        while abs(swCorner2) < innerR:
            area += rectOverlapArea(swCorner2, g, g, innerR)
            swCorner2 += Vector2(skip, 0.0)
        swCorner += Vector2(0.0, skip)
    return area * 4

def bruteForceGapArea(innerR, r, g):
    swCorner = Vector2(r, r)
    skip = 2 * r + g
    area = 0
    while abs(swCorner) < innerR:
        swCorner2 = swCorner
        while abs(swCorner2) < innerR:
            area += rectOverlapArea(swCorner2, g, g, innerR)
            swCorner2 += Vector2(skip, 0.0)
        swCorner += Vector2(0.0, skip)
    return area * 4

def main():
    N = int(raw_input())
    for n in xrange(1, N+1):
        f, R, t, r, g = map(float, raw_input().split())
        if g <= 2 * f:
            result = 1
        else:
            total = math.pi * R**2
            gaps = gapArea(R - t - f, r + f, g - 2 * f)
            result = (total - gaps) / total
        print('Case #{}: {}'.format(n, result))

if __name__ == "__main__":
    main()
