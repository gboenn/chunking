# cost.py
# Copyright (C) 2018 Georg Boenn
# GNU General Public License version 3.0
# Free Software Foundation

from math import sqrt
from digest import *
from float_to_ratio_func import *

#s1 = [0.3333333333333333, 0.3333333333333333, 0.041666666666666664, 0.041666666666666664, 0.16666666666666666, 0.08333333333333333]
#s2 = [0.3125, 0.3125, 0.041666666666666664, 0.041666666666666664, 0.20833333333333334, 0.08333333333333333]
#s3 = [0.28125, 0.28125, 0.046875, 0.046875, 0.21875, 0.125]

def cost_fun(a):
    #accumulated durations
    #digestibility of an integer (denominator)
    #small value => high digestibility (low complexity)
    temp = []
    col = 0.
    dig = 0.
    for k in range(len(a)):
        col = col + a[k]
        temp.append(col)
 #   print temp
    for k in range(len(temp)):
        ratio = float2ratio(temp[k])
        dig = dig + digest(ratio[1])
    return dig

#print cost_fun(s1)
#print cost_fun(s2)
#print cost_fun(s3)

def cost_fun_harm(a):
    #Barlow: harmonicity of a ratio
    #high value => high harmonicity
    temp = []
    col = 0.
    dig = 0.
    for k in range(len(a)):
        col = col + a[k]
        temp.append(col)
 #   print temp                                                                                                                                               
    for k in range(len(temp)):
        ratio = float2ratio(temp[k])
        r = digest(ratio[0]) + digest(ratio[1])
        if (r > 0.):
            dig = dig + (1. / r) 
    return dig

    
def cost_fun_euclid(a,b):
    #euclidean distance
    #small value => small distance
    col = 0.
    for k in range(len(a)):
        d = a[k] - b[k]
        d = d * d
        col = col + d
    col = sqrt(col)
    return col


def cost_fun_ratios(a):
    # ratios between durations
    col = 0.
    for k in range(len(a)-1):
        ratio = a[k] / a[k+1]
        frac = float2ratio(ratio)
        r = digest(frac[0]) + digest(frac[1])
        if (r > 0.):
            col = col + (1. / r)
    return col

def cost_fun_numerator(a):
    #digestibility of an integer (numerator)                     
    dig = 0.
    for k in range(len(a)):
        ratio = float2ratio(a[k])
        dig = dig + digest(ratio[0])
    return dig
