#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'closestNumbers' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts INTEGER_ARRAY arr as parameter.
#

def closestNumbers(arr):
    arr= sorted(arr)
    
    final_arr= []
    diff = abs(arr[1]-arr[0])
    
    for i in range(2, len(arr)):
        temp_diff = abs(arr[i] - arr[i-1])
        diff = min(temp_diff, diff) 
    
    for i in range(1, len(arr)):
        temp_diff = abs(arr[i] - arr[i-1])
        if temp_diff == diff:
            final_arr.append(arr[i-1])        
            final_arr.append(arr[i])        
    
    return final_arr

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    result = closestNumbers(arr)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
