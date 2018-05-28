# coding: utf-8

from io import open
import sys
import time
import numpy as np
import random
import matplotlib.pyplot as plt


class CutMethod(object):
    ROTATION = True
    NOT_ROTAION = False
    AS_WIDTH = True
    AS_LENGTH = False
    CONVEGE = list()
    
    def __init__(self, space, blocks, cut_method=None):
        self.spaces = [space]
        self.blocks = blocks
        
        if bool(cut_method) == False:
            self.DNAs = []
            
            DNA = [[], [], []]
            for i in range(len(blocks)):
                DNA[0].append(i)
                DNA[1].append(self.AS_WIDTH)
                DNA[2].append(self.NOT_ROTAION)
            self.DNAs.append(DNA)
            
            DNA = [[], [], []]
            for i in range(len(blocks)):
                DNA[0].append(i)
                DNA[1].append(self.AS_LENGTH)
                DNA[2].append(self.ROTATION)
            self.DNAs.append(DNA)
    
    def cut_block(self, block, spaces):
        blocks = self.blocks    
        split_method = block[1]
        rotation = block[2]
        # if rotation w and l need to exchange their value
        w, l = blocks[block[0]] if rotation == self.NOT_ROTAION else blocks[block[0]][::-1]
        
        loc = None
        for it, space in enumerate(spaces):
            W, L, x, y = space
            
            if w <= W and l <= L:
                loc = (x, y)
                
                if split_method == self.AS_WIDTH:
                    s1 = (W, L-l) + (x, y+l) # x is the W dim loc and y is the L dim loc
                    s2 = (W-w, l) + (x+w, y)
                    spaces[it:it+1] = [s1, s2]
                
                else:
                    s1 = (W-w, L) + (x+w, y)
                    s2 = (w, L-l) + (x, y+l)
                    spaces[it:it+1] = [s1, s2]
                
                break
                
        new_spaces = []
        
        for x in spaces:
            if x[0] != 0 and x[1] != 0:
                new_spaces.append(x)
        
        return new_spaces, loc 
    
    def evalue(self, DNA):
        spaces = self.spaces[:]
        spaces[0] += (0, 0)
        loc = [None]*len(self.blocks)
        
        DNA = [(x, y, z) for x,y,z in zip(DNA[0],DNA[1],DNA[2])] # nothing special don't mind
        
        for it, block in enumerate(DNA):
            spaces, loc[it] = self.cut_block(block, spaces)
        
        
        left_area = sum([x*y for x, y, _, _ in spaces])
        return left_area, spaces, loc
    
    def get_next_generation(self, n=10):
        DNAs = self.DNAs
        
        alive_DNAs = self.select_individual(DNAs[:])
        new_DNAs = self.mutation(alive_DNAs[:]) + self.sexual(alive_DNAs[:])
        
        self.DNAs = alive_DNAs + new_DNAs
        self.delete_same()
    
    def select_individual(self, DNAs, n=10, prob=0.30):
        evalue = self.evalue

        compare_key = lambda x: evalue(x)[0]
        
        DNAs = sorted(DNAs, key=compare_key, reverse=False) 
        must_alive = DNAs[:n]
        
        self.CONVEGE.append(evalue(DNAs[0])[0])
        
        bad_DNA = []
        for DNA in DNAs[n:]:
            if random.random() < prob:
                bad_DNA.append(DNA)
        
        return must_alive + bad_DNA
        
    def mutation(self, DNAs, prob=0.20):
        # copy DNAs
        for i in range(len(DNAs)):
            DNAs[i] = DNAs[i][:]
            for j in range(len(DNAs[i])):
                DNAs[i][j] = DNAs[i][j][:]
        
        
        _range = range(len(DNAs[0][0]))
        del_list = []
        for i in range(len(DNAs)):
            mutation_flag = False
            if random.random() < prob:
                mutation_flag = True
                for it in range(len(DNAs[0][0])//4):
                    k, j = random.sample(_range, 2)
                    DNAs[i][0][k], DNAs[i][0][j]= DNAs[i][0][j], DNAs[i][0][k] 
                
            for it in range(len(DNAs[i][0])):
                if random.random() < prob:
                    mutation_flag = True
                    DNAs[i][1][it] = not DNAs[i][1][it]
                    
                if random.random() < prob:
                    mutation_flag = True
                    DNAs[i][2][it] = not DNAs[i][2][it]
            
            #if random.random() < prob:
            #    mutation_flag = True
            #    t, k = random.sample(_range, 2)
            #    DNAs[i][1][t] = not DNAs[i][1][t]
            #    DNAs[i][1][k] = not DNAs[i][1][k]
            #if random.random() < prob:
            #    mutation_flag = True
            #    t, k = random.sample(_range, 2)
            #    DNAs[i][1][t] = not DNAs[i][1][t]
            #    DNAs[i][1][k] = not DNAs[i][1][k]
            
            if mutation_flag == False:
                del_list.append(DNAs[i])
        for i in range(len(del_list)):
            DNAs.remove(del_list[i])

        return DNAs
    
    def sexual(self, DNAs):
        for i in range(len(DNAs)):
            DNAs[i] = DNAs[i][:]
            for j in range(len(DNAs[i])):
                DNAs[i][j] = DNAs[i][j][:]
        
        
        _range = range(len(DNAs[0][0]))
        n = len(DNAs)
        select_num = int(n/4)
        
        sex_DNAs = random.sample(DNAs, select_num)
        
        if bool(sex_DNAs) == False:
            return []
        
        new_DNAs = []
        for DNA in sex_DNAs:
            
            DNA2 = random.choice(sex_DNAs)
            index = random.choice(_range)
            
            g1 = DNA[0][index]
            g2 = DNA2[0][index]
            
            for i in range(len(DNA[0])):
                if DNA[0][i] == g2:
                    DNA[0][i] = DNA[0][index]
                    DNA[1][i] = DNA[1][index]
                    DNA[2][i] = DNA[2][index]
                    break
                    
            for i in range(len(DNA2[0])):
                if DNA2[0][i] == g1:
                    DNA2[0][i] = DNA2[0][index]
                    DNA2[1][i] = DNA2[1][index]
                    DNA2[2][i] = DNA2[2][index]
                    break
            
            DNA[0][index], DNA2[0][index] = DNA2[0][index], DNA[0][index]
            DNA[1][index], DNA2[1][index] = DNA2[1][index], DNA[1][index]
            DNA[2][index], DNA2[2][index] = DNA2[2][index], DNA[2][index]
            
            new_DNAs.append(DNA)
            new_DNAs.append(DNA2)
        
        return new_DNAs
    
    def delete_same(self):
        DNAs = self.DNAs
        
        new_DNAs = []
        for i in range(len(DNAs)):
            if DNAs[i] not in new_DNAs:
                flag = False
                for gen in new_DNAs:
                    if self.evalue(gen)[0] == self.evalue(DNAs[i])[0]:
                        flag = True
                        # print ("deleted\n")
                        break
                if flag == False: new_DNAs.append(DNAs[i][:])
                
        DNAs[:] = new_DNAs[:]
        
    def plot(self, k):
        left, s, loc =  self.evalue(self.DNAs[k])
        
        color = list(range(1, len(loc)+1))
        random.shuffle(color)
        
        pi = np.zeros(self.spaces[0])
        for i, d in enumerate(self.DNAs[k][0]):
            if loc[i] != None:
                x, y = loc[i]
                
            else:
                continue
                
            w,l = self.blocks[d] if self.DNAs[k][2][i] == self.NOT_ROTAION else self.blocks[d][::-1]
            
            for t in range(x,x+w):
                for j in range(y,y+l):
                    pi[t][j] = color[i]

        #plt.ion()
        plt.imshow(pi)
        area = self.spaces[0][1] * self.spaces[0][0]
        title = "Usage %.3f " % ((area - left)/area * 100) + " %"
        plt.title(title)
        plt.show()
        #plt.pause(5)
        #plt.close()


def main():
    epoch = int(sys.argv[1])
    compare_key = lambda x: x[0]*x[1]
    lst = []
    with open('lw292.txt') as f:
        lst = f.readlines()
        lst = [i.strip().split() for i in lst]
        lst = [(int(x[0]), int (x[1])) for x in lst]

    lst = sorted(lst, key=compare_key, reverse=True)
    # print lst

    packing = CutMethod((60, 30), lst)

    s_time = time.clock()
    data = []
    for i in range(epoch):
        if i % 50 == 0: 
            print ("this is the ", i, "th epoch", end="\n", flush=True)
            # sys.stdout.flush()
        packing.get_next_generation()

    e_time = time.clock()

    cost_time = e_time - s_time
    print ("Cost Time: %d min %d s " % (int(cost_time / 60), int (cost_time % 60)))

    for i in range(10):
        packing.plot(i)
    
    #plt.ion()
    plt.plot(range(len(packing.CONVEGE)),packing.CONVEGE)
    #plt.pause(5)
    #plt.close()
    plt.show()
    print ("OVER")


if __name__ == "__main__":
    main()

