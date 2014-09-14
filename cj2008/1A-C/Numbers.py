#!/usr/bin/env python

from __future__ import print_function

def mul_2x2_Matrix_mod1000(((a00, a01), (a10, a11)), ((b00, b01), (b10, b11))):
    return (((a00 * b00 + a01 * b10) % 1000, (a00 * b01 + a01 * b11) % 1000),
            ((a10 * b00 + a11 * b10) % 1000, (a10 * b01 + a11 * b11) % 1000))

def apply_2x2_Matrix_mod1000(((a00, a01), (a10, a11)), (v0, v1)):
    return ((v0 * a00 + v1 * a01) % 1000, 
            (v0 * a10 + v1 * a11) % 1000)

stepMatrix = ((6, -4), (1, 0))
startVector = (6, 2)

def solveCase(n):
    binDigits = '{:b}'.format(n)
    matrix = stepMatrix
    for digit in binDigits[1:]:
        matrix = mul_2x2_Matrix_mod1000(matrix, matrix)
        if digit == '1':
            matrix = mul_2x2_Matrix_mod1000(matrix, stepMatrix)
    return (apply_2x2_Matrix_mod1000(matrix, startVector)[1] - 1) % 1000

def main():
    T = int(raw_input())
    for t in xrange(1, T+1):
        n = int(raw_input())
        print('Case #{}: {:03}'.format(t, solveCase(n)))

if __name__ == '__main__':
    main()
