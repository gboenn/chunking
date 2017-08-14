 #!/bin/bash

./chunking -m propseries 89 8 1.618
./chunking -m anaphrases text/testin.txt 
./chunking -m partition 30 0 1 91 9 2 0 0 0
./chunking -m intstrings text/integer_rhythm1.txt text/integer_rhythm2.txt
./chunking -m farey2binary 7 4 0
./chunking -m divisors
./chunking -m permutations
./chunking -m permutations2
./chunking -m fpoly 20 5 4
./chunking -m printfarey 5
./chunking -m crhythm 5 4
./chunking -m lookup 'I-'
./chunking -m sentence 30 2
./chunking -m anaphrases text/a1.txt
./chunking -m printphrases text/a2.txt text/mel.txt
