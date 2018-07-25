# grouping_dev01.py
# Copyright (C) 2018 Georg Boenn
# GNU General Public License version 3.0
# Free Software Foundation
# Usage: python grouping_dev01.py onsets.txt theshold_seconds ternary_or_binary_meter
import math
import sys

import numpy as np
#from primes_tab import *
from float_to_ratio_func import *
from fareytab import *
from digest import *
from expwindow import * 
from permut_lists import *
from cost import *
from transcription import *

#analysis of a text file with a list of note onsets (one per line)
#outputs groupings of onsets (duration classes)
#normalizes duration classes
#takes mean of duration classes
#converts mean decimals to fractions (continuous fraction expansion)
#quantizes mean decimals to farey sequence ratios with minimum complexity (modified Barlow's digestibility)
#and minimum Euclidean distance to performed IOIs

if len(sys.argv) < 3:
    print("Usage: %s <filename> <threshold> <switch ratio4>" % sys.argv[0])
    sys.exit(1)

filename = sys.argv[1]
threshold = float(sys.argv[2])
flag = int(sys.argv[3])

onsetsA = []

with open(filename) as f:
    for line in f:
        #one onset time in seconds per line
        onsetsA.append(float(line))

def quantize(markers):
    onsets = markers
    onsets0 = []
    durations = []

    plotfile = filename + '.dat'
    fdat = open(plotfile, 'w+')

    dursfile = filename + '.durs'
    fdurs = open(dursfile, 'w+')

    print "onsets:"
    print onsets
    print "duration ratios from onsets:"
    print dur_ratios(onsets)

    sum_durs = 0.

    for k in range(len(onsets) -1):
        o1 = onsets[k]
        o2 = onsets[k+1]
        odiff = o2-o1
        durations.append(odiff)
        onsets0.append(odiff)
        sum_durs += odiff

    print "length of window = ", sum_durs, " s."

    print "IOTs:"
    print durations
    onsets = durations

    #print dur_ratios(onsets)

    onsets.sort()

    print onsets

    for k in range(len(onsets)):
        s = str(onsets[k]) + '\n'
        fdat.write(s)
    
    groups = []
    groups.append([])
    gc = 0
    groups[gc].append(onsets[0])
    for k in range(len(onsets)-1):
        o1 = onsets[k]
        o2 = onsets[k+1]
        if (o2-o1) < threshold:
            groups[gc].append(o2)
    #        print o1, o2
        else:
    #        print "new"
            gc += 1
            groups.append([])
            groups[gc].append(o2)

    print "groups:"
    print groups, " has ", gc+1, " groups." 

    durclasses = []
    norm_durclasses = []
    length_durclasses = []
    order_classes = []
    for o in range(len(onsets0)):
        for k in range(gc+1):
            count = 0
            for m in range(len(groups[k])):
                if (onsets0[o] == groups[k][m]):
                    durclasses.append([k,onsets0[o]])
                    norm_durclasses.append([k,onsets0[o]/sum_durs])
                    order_classes.append(k)
                    count += 1
                    break

    print "-----------------------------"
    for k in range(gc+1):
        length_durclasses.append(len(groups[k]))

    print "duration classes:"   
    print durclasses
    print "normalized classes:"
    print norm_durclasses            
    print "order of classes"
    print order_classes

    mean_classes = []
    for k in range(gc+1):
        temp = []
        for i in range(len(norm_durclasses)):
            if (norm_durclasses[i][0] == k):
                temp.append(norm_durclasses[i][1])
        mean_dur = 0.
        if (len(temp) > 0):
            for i in range(len(temp)):
                mean_dur += temp[i]
            mean_dur /= len(temp)
        mean_classes.append([k,mean_dur])


    print "means of normalized classes:"
    print mean_classes

    print "means as fractions:"
    for i in range(len(mean_classes)):
        print float2ratio(mean_classes[i][1])

# ratios for a ternary meter
    ratio3=[2,3,1,1,5,6,1,3,1,2,5,12,7,12,1,6,1,4,5,24,7,24,1,12,1,8,7,48,1,24,1,16,7,96,1,48,1,32,8,9,4,9,2,9,1,9,1,18,1,36,4,15,2,15,1,15,1,30,1,60]
# ratios for a binary meter
    ratio4=[1, 2, 3, 4, 5, 8, 1, 4, 3, 8, 5, 16, 7, 16, 1, 8, 3, 16, 5, 32, 7, 32, 1, 16, 3, 32, 7, 64, 1, 32, 3, 64, 7, 128, 1, 64, 3, 128, 2, 3, 1, 3, 1, 6, 1, 12, 1, 24, 1, 48, 1, 5, 1, 10, 1, 20, 1, 40, 1, 80]

    fareytabletest=[]
    if (flag > 0):
        fareytabletest = ratio3
        print "using ratio3"
    else:
        fareytabletest = ratio4
        print "using ratio4"

    fareydigest = []
    for i in range(0, len(fareytabletest), 2):
        p = float(fareytabletest[i])
        q = float(fareytabletest[i+1])
        fareydigest.append([(p/q), digest(q), p, q])

    #ratio3 is not sorted
    fareydigest.sort(key=lambda x: x[0])

    print fareydigest

    gauss_table_length = 1024
    win = expwin(gauss_table_length)

    #print win

    solutions = []

    #num_qdurs = 8 with larger list of fareytabletest
    #allow for num_qdurs durations per class
    num_qdurs = 6
    for k in range(len(mean_classes)):
        srange = 1. * mean_classes[k][1]
        max = mean_classes[k][1] + 0.5 * srange
        min = mean_classes[k][1] - 0.5 * srange
        if max > 1.0: max = 1.
        if min < 0.0: min = 0.
        print "search area:"
        print min, mean_classes[k][1], max
        quant_cand = list()
        for el in fareydigest:
            if (el[0] >= min and el[0] <= max and el[1] != 0.):
                n = int(float(gauss_table_length) * (el[0] - min)/(max - min))
                w = win[n]
                quant_cand.append([el[0], w/el[1], el[2], el[3], w])
        quant_cand.sort(key=lambda x: x[1])
        quant_cand.reverse()
        count = 0
        slist = []
        print "solutions:"
        for p in quant_cand:
            p.append(k)
            print p
            slist.append(p)
            count += 1
            if (count > (num_qdurs-1)):
                break
        solutions.append(slist)

    #print solutions

    # create all combinations of possible durations per class
    print "there are ", len(solutions), " duration classes"
    slist = []
    for l in solutions:
        contrib = []
        for m in l:
            contrib.append(m[0])
        slist.append(contrib)

    clist =  list_combinations(slist)

    #map clist to normalized duration classes: norm_durclasses via order_classes
    dlist = []
    for c in clist:
        d = []
        s = 0.
        for k in order_classes:
            d.append(c[k])
            s = s + c[k]
        if (math.fabs(s - 1.0) < 0.0001):
            dlist.append(d)
        s = 0.


    orig = []
    for k in norm_durclasses:
        orig.append(k[1])
        s = str(k[1]) + '\n'
        fdurs.write(s)

    print "original durations:"
    print orig
    print "quantized:"
    reslist = []
    for d in dlist:
        c = cost_fun(d)
        reslist.append([d, c, cost_fun_euclid(d,orig), cost_fun_numerator(d)])
#                       0  1  2                         3
#sort after cost functions:

    reslist.sort(key=lambda x: x[1])
    reslist.sort(key=lambda x: x[3])
    quantresult = reslist[:10]
    #take first 10  and sort after x[2] (euclidean fun)
    quantresult.sort(key=lambda x: x[2])

#select results:

    qoutput = []
    count = 0
    for q in quantresult:
        if (count == 0):
            qoutput.append(q)
            qoutput.append(transcribe(q[0]))
            count = count + 1
        elif (q[3] == 0.):
            qoutput.append(q)
            qoutput.append(transcribe(q[0]))
            break
    
    return qoutput, (60./(sum_durs/3.))

bpm = 0.
rcan, bpm =  quantize(onsetsA)

outcount = 0
for r in rcan:
    print r, bpm
    if (outcount % 2 == 0):
        quantfile = filename + '.quant' + str(outcount)
        #for plotting:
        fquant = open(quantfile, 'w+')
        quantlist = r[0]
        for k in quantlist:
            s = str(k) + '\n'
            fquant.write(s)
        fquant.close()
    else:
        transfile = filename + '.snmr' + str(outcount)
        ftrans = open(transfile, 'w+')
        s = str(r)
        ftrans.write(s)
        ftrans.close()
        
        lilyfile = filename + '.ly' + str(outcount)
        write_lily(r, lilyfile, "3/4")
    outcount += 1
