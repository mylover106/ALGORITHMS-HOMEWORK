# coding: utf-8

from __future__ import division, print_function
from io import open
import numpy as np
import sys


def get_list(filename1, filename2):
    with open(filename1) as f:
        l = f.read()
        l = l.split()
        list1 = l
    with open(filename2) as f:
        l = f.read()
        l = l.split()
        list2 = l
    return list1, list2


def find_max_commen(seqs):
    dp = np.zeros(
        (len(seqs[0]), len(seqs[1])) 
    )
    
    for i in range(0, dp.shape[0]):
        if seqs[0][i] == seqs[1][0]:
            dp[i][0] = 1
    
    for j in range(0, dp.shape[1]):
        if seqs[1][j] == seqs[0][0]:
            dp[0][j] = 1
    
    for i in range(1, dp.shape[0]):
        for j in range(1, dp.shape[1]):
            if seqs[0][i] == seqs[1][j]:
                dp[i][j] = max(dp[i-1][j-1]+1, dp[i][j-1], dp[i-1][j], dp[i][j])
    
    return max(dp.reshape(-1))



if __name__ == "__main__":
    filename1 = sys.argv[1]
    filename2 = sys.argv[2]
    file_pair = get_list(filename1, filename2)
    commen_num = find_max_commen(file_pair)
    print("%s %s 相似度为： %.2f " %(filename1, filename2 ,(
        100 * commen_num / min(
        len(file_pair[0]), len(file_pair[1]))
         )), end='%\n')

