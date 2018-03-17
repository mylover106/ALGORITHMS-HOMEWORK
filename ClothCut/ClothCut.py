# coding: utf-8

import numpy as np
import matplotlib.pyplot as plt
from pprint import pprint


def maxHigh(solve):
    max_high = solve[-1][1][0][0] # solve[1][0] is the surface as the ans_structure
    for h, _ in solve[-1][1]:
        if max_high < h:
            max_high = h
    return max_high



def selectBestSolve(solves):
    bestSolve = solves[0]
    for i in range(1,len(solves)):
        if maxHigh(solves[i]) < maxHigh(bestSolve):
            bestSolve = solves[i]
    return bestSolve


def updateSurface(nowSize, Surface, loc):
    width = nowSize[1]
    high = nowSize[0]
#     print "old", Surface, loc, nowSize
    for i in range(len(Surface)):
        if Surface[i][1] == loc:
            start_index = i
        if Surface[i][1] <= loc + width:
            end_index = i
    plot_high = maxHigh([(0, Surface[start_index:end_index+1], 0)])
    high += plot_high
    newSurface = [(high, loc), (Surface[end_index][0], loc + width)]
#     newSurface.extend(Surface[end_index+1:])
    newSurface = Surface[:start_index] + newSurface + Surface[end_index + 1:]
#     print "newsurface", newSurface
    return newSurface, plot_high



def recursiveCut(SizeList, nowSize, Surface, loc):
    if len(SizeList) == 0:
#         print Surface, loc
        newSurface, plot_high = updateSurface(nowSize, Surface, loc)
        return [[nowSize, newSurface, loc, plot_high]]
    else:
        nowSolves = []
        newSurface, plot_high = updateSurface(nowSize, Surface, loc)
        for s in range(len(SizeList)):
            for _, next_loc in newSurface:
#                 print _, next_loc
                if Width - next_loc >= SizeList[s][1]:
                    nowSolves.append(recursiveCut(SizeList[:s] + SizeList[s+1:], 
                                                 SizeList[s], newSurface, next_loc))
#         print nowSolves
        bestSolve = selectBestSolve(nowSolves)
        bestSolve = [[nowSize, newSurface, loc, plot_high]] + bestSolve
#         print "bestSolve", bestSolve
        return bestSolve



def plotAns(ans, Width):
    High = maxHigh(ans)
    picture = np.ones((High, Width))
    color = 20
    for block in ans:
        h, w = block[0][0], block[0][1]
        plot_loc, plot_high = block[2], block[3]
        for i in range(plot_loc, plot_loc + w):
            for j in range(plot_high, plot_high + h):
                picture[j][i] = color
        color += 5
    plt.imshow(picture)



if __name__ == "__main__":
    
    Width = 100
    Size = [(50, 7), (29, 43), (30, 77), (10, 21)] # high first (high, width)
    Surface = [(0, 0)]
    
    ans = recursiveCut(Size, (0,0), Surface, 0)
    
    pprint(ans)
    plotAns(ans, Width)




"""
ansStructure
[
[Size, Surface, plot_loc, plot_high] // the Surface is the Surface that after added the nowSize
[],                  // loc is the left location the Size put down
[],
[],...[n]
]
"""

