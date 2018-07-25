# permut_lists.py
# Copyright (C) 2018 Georg Boenn
# GNU General Public License version 3.0
# Free Software Foundation

def list_combinations (allsets):
    #input a list of lists
    #output all possible combinations between the elements of the lists with no repetitions

#    print allsets

    max_exponent = len(allsets)
    print range(max_exponent)
    alllengths = []
    for k in range(max_exponent):
        alllengths.append(len(allsets[k]))

#    print alllengths

    repeat_el = []
    repeat_pat = []

    for k in range(max_exponent):
        n = k+1
        fac = 1
        while(n<max_exponent):
            fac *= alllengths[n]
            n = n+1
        repeat_el.append(fac)

#    print repeat_el

    for k in range(max_exponent):
        n = k-1
        fac = 1
        while(n >= 0):
            fac *= alllengths[n]
            n = n-1
        repeat_pat.append(fac)

#    print repeat_pat

    all_combs = []
    for k in range (len(allsets)):
        contrib = []
        for m in range (len(allsets[k])):
            for l in range(repeat_el[k]):
                contrib.append(allsets[k][m])
        all_combs.append(contrib)

#    print all_combs

    all_combs2 = []
    for k in range(len(all_combs)):
        contrib = []
        for m in range(repeat_pat[k]):
            for l in range(len(all_combs[k])):
                contrib.append(all_combs[k][l])
        all_combs2.append(contrib)

#    print all_combs2

    all_combs3 = []

    m = 0
    limit = len(all_combs2[0])
    while (m < limit):
        contrib = []
        for k in range(len(all_combs2)):
            contrib.append(all_combs2[k][m])
        m = m+1
        all_combs3.append(contrib)

#        print all_combs3
    return all_combs3



#set1 = ['a','b','c','d']
#set2 = ['e','f','g',]
#set3 = ['j','k',]
#set4 = ['n']

#set1 = ['a','b','c','d']
#set2 = ['e','f','g','h']
#set3 = ['j','k','l','m']
#set4 = ['n','o','p','q']

#sset = []
#sset.append(set1)
#sset.append(set2)
#sset.append(set3)
#sset.append(set4)

#outp =  list_combinations(sset)
#print outp
#print len(outp)
