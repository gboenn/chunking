# float_to_ratio_func.py
# Copyright (C) 2018 Georg Boenn
# GNU General Public License version 3.0
# Free Software Foundation

import math as m

def float2ratio(r):

    p = []
    q = []
    x = []
    a = []

    rabs = m.fabs(r)

#print r, rabs

    n = 10

    for i in range(n+1):
        p.append(0)
        q.append(0)
        x.append(0.)
        a.append(0)

    p[0] = 1
    q[0] = 0
    p[1] = int(rabs)
    q[1] = 1
    x[0] = rabs
    a[0] = int(rabs)

#print a[0]
#print float(a[0])

    for i in range(n-1):
        i += 1
        if (x[i-1] - float(a[i-1]) == 0.):
            break
        x[i] = 1. / (x[i-1] - float(a[i-1]))
        a[i] = int(x[i])
        p[i+1] = a[i] * p[i] + p[i-1]
        q[i+1] = a[i] * q[i] + q[i-1]

    if (r < 0.):
        for i in range(n+1):
            p[i] = -p[i]
    

#print a
#print p
#print q

    def_err = 0.00001

    P = 0
    Q = 1
    ERR = 0.
    for i in range(n):
        if (q[i+1] != 0):
            temp = float(p[i+1]) / float(q[i+1])
            ferr = r - temp
            if (m.fabs(ferr) < def_err):
                P = p[i+1]
                Q = q[i+1]
                ERR = ferr
                break

#print r, " = ", P, "/", Q, " + ", ERR 
    return [P,Q]

#print float2ratio(0.3333)
