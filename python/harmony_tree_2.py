import sys

hin = 'C7'
if len(sys.argv) < 2:
    print("Constructs a chord from types C-7, C7, Cmaj7, Cmmaj7.\nUsage: %s <type>" % sys.argv[0])
    sys.exit(-1)

hin = sys.argv[1]

harmony = []

htype = ['Cm7', 'C7', 'Cmaj7', 'Cmmaj7']


# b13 13 0         2 bits  00  01  11
# 11 #11 0         2 bits  00  01  11
# b9 9 #9 b9#9 0   4 bits  0000 0001 0011 0111 1111
# b5 5 0           4 bits  0000 0001 0011 1111
# ----------
# b7 b7 7  7 0
# b3  3 3 b3 0     3 bits  000 001 010 011 111
# ----------
# 1 0              1 bit   0   1

# 2 bytes code fo one harmony = 16 bits
# 2 * 5 * 4 * 5 * 3 * 3 = 1800 combinations

# left-shift:
# 15      12        8           4       2      0
# 0 | 1 2 3 | 4 5 6 7 | 8 9 10 11 | 12 13 | 14 15
# 0           -> with or without fundamental 
# 1 2 3       -> one of four 3-7 configurations: Cm7, C7, Cmaj7, Cmmaj7
# 4 5 6 7     -> 5th
# 8 9 10 11   -> 9th
# 12 13       -> 11th
# 14 15       -> 13th

def check_bit4(input):
    mask=0b1000
    if input&mask >0:
        return "on"
    else:
        return "off"

print check_bit4(0b1100)

# binary to hex
# binary to char
# + vice versa


import binascii

t='A'
tx =bin(int(binascii.hexlify(t), 16))
print tx
#'0b1000001'
n=int(tx,2)
print n
#65
print binascii.unhexlify('%x' % n)
#'A'


print binascii.hexlify('A')
print hex(0b111)

print bin(0xf)

print bin(0b10001110 & (0x7 << 1))

#>>> bin((0x1 << 3) + 0b001)
#'0b1001'

#>>> bin((0x1 << 15) + (0b001 << 12))
#'0b1001000000000000'
