# transcription.py
# Copyright (C) 2018 Georg Boenn
# GNU General Public License version 3.0
# Free Software Foundation

import math as m

transcript = [
[0.016666666666666666, 11.066666666666666, 1.0, 60.0, "[10 .]", "\\tuplet 5/4 {sn64}"],
[0.020833333333333332, 6.666666666666666, 1.0, 48.0, "[8 .]", "sn64"],
[0.027777777777777776, 7.333333333333333, 1.0, 36.0, "[6 .]", "\\tuplet 3/2 {sn32}"],
[0.03125, 5.0, 1.0, 32.0, "[16 -]", "sn64."],
[0.03333333333333333, 10.066666666666666, 1.0, 30.0, "[5 .]", "\\tuplet 5/4 {sn32}"],
[0.041666666666666664, 5.666666666666666, 1.0, 24.0, "[4 .]", "sn32"],
[0.05555555555555555, 6.333333333333333, 1.0, 18.0, "[3 .]", "\\tuplet 3/2 {sn16}"],
[0.0625, 4.0, 1.0, 16.0, "[8 -]", "sn32."],
[0.06666666666666667, 9.066666666666666, 1.0, 15.0, "5 I", "\\tuplet 5/4 {sn16}"],
[0.07291666666666667, 7.666666666666666, 7.0, 96.0, "[16 H~-]", "sn32.."],
[0.08333333333333333, 4.666666666666666, 1.0, 12.0, "[.]", "sn16"],
[0.1111111111111111, 5.333333333333333, 1.0, 9.0, "[3 I]", "\\tuplet 3/2 {sn8}"],
[0.125, 3.0, 1.0, 8.0, "[4 -]", "sn16."],
[0.13333333333333333, 9.066666666666666, 2.0, 15.0, "[5 H]", "\\tuplet 5/4 {sn8}"],
[0.14583333333333334, 6.666666666666666, 7.0, 48.0, "[8 H~-]", "sn16.."],
[0.16666666666666666, 3.6666666666666665, 1.0, 6.0, ".", "sn8"],
[0.20833333333333334, 5.666666666666666, 5.0, 24.0, ".~[4.]", "sn8~sn32"],
[0.2222222222222222, 5.333333333333333, 2.0, 9.0, "[3 H]", "\\tuplet 3/2 {sn4}"],
[0.25, 2.0, 1.0, 4.0, "[-]", "sn8."],
[0.26666666666666666, 9.066666666666666, 4.0, 15.0, "[5 W]", "\\tuplet 5/4 {sn}"],
[0.2916666666666667, 5.666666666666666, 7.0, 24.0, "[4 H~-]", "sn8.."],
[0.3333333333333333, 2.6666666666666665, 1.0, 3.0, "I", "sn4"],
[0.4166666666666667, 4.666666666666666, 5.0, 12.0, "I~[.]", "sn4~sn16"],
[0.4444444444444444, 5.333333333333333, 4.0, 9.0, "[3 W]", "\\tuplet 3/2 {sn2}"],
[0.5, 1.0, 1.0, 2.0, "-", "sn4."],
[0.5833333333333334, 4.666666666666666, 7.0, 12.0, "[H~-]", "sn4.."],
[0.6666666666666666, 2.6666666666666665, 2.0, 3.0, "H", "sn2"],
[0.8333333333333334, 3.6666666666666665, 5.0, 6.0, "H~.", "sn2~sn8"],
[0.8888888888888888, 5.333333333333333, 8.0, 9.0, "[3 W~W]", "\\tuplet 3/2 {sn1}"],
[1.0, 0.0, 1.0, 1.0, "H~I", "sn2."]
]

def transcribe(a):
    result = []
    durs = a
#    print durs
    for f in range(len(durs)):
        for t in transcript:
            if (m.fabs(durs[f] - t[0]) < 0.00001):
               result.append(t[4]) 
    return result

def encode_lily(durs):
    result = []
    for f in range(len(durs)):
        for t in transcript:
            if (m.fabs(durs[f] - t[0]) < 0.00001):
               result.append(t[5])
    return result


def dur_ratios(w):
#take list of onstes and analyse duration ratios (IOT ratios)
    result = []
    durs = []
    for k in range(len(w)-1):
        iot = w[k+1] - w[k]
        durs.append(iot)
    for k in range(len(durs)-1):
        r = durs[k+1] / durs[k]
        result.append(r)
    return result
        
def start_lily():
    return "\\version \"2.18.2\" \\score { \\new DrumStaff  \\drummode{"

def end_lily():
    return "} \\layout {} \\midi {\\tempo 8 = 90 }}"


def write_lily(snmr, filename, meter):
    fquant = open(filename, 'w+')
    fquant.write(start_lily())
    fquant.write("\n")
    meterstr = "\\time " + meter + " "
    fquant.write(meterstr)
    for k in snmr:
        for s in transcript:
#            print "==",k,s[4]
            if (k==s[4]):
                fquant.write(s[5])
                fquant.write(" ")
    fquant.write("\n")
    fquant.write(end_lily())
    fquant.close()


