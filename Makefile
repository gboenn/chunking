# Makefile for chunking - last updated May 26 2017
# Makefile for chunking - last updated Aug 7 2017
    
SRCS = Alea.cpp AlgoComp.cpp Interpret.cpp Main.cpp Modul.cpp TextIO.cpp \
Power.cpp Visitor.cpp Farey.cpp FareyVisitor.cpp Ratio.cpp \
FareyFilter.cpp SmoothFilter.cpp ProbFilter.cpp PrimeFilter.cpp \
FareyFilterFarey.cpp DList.cpp SternBrocot.cpp ReciprocalFilter.cpp SubdivisionFilter.cpp \
Christoffel.cpp

HDRS = Alea.h AlgoComp.h Interpret.h Modul.h TextIO.h \
Power.h Visitor.h Farey.h FareyVisitor.h Ratio.h \
FareyFilter.h SmoothFilter.h ProbFilter.h PrimeFilter.h \
FareyFilterFarey.h DList.h SternBrocot.h ReciprocalFilter.h SubdivisionFilter.h \
Christoffel.h


OBJS = Alea.o AlgoComp.o Interpret.o Main.o Modul.o TextIO.o \
Power.o Visitor.o Farey.o FareyVisitor.o Ratio.o \
FareyFilter.o SmoothFilter.o ProbFilter.o PrimeFilter.o \
FareyFilterFarey.o DList.o SternBrocot.o ReciprocalFilter.o SubdivisionFilter.o \
Christoffel.o

CC = g++
#CC = g++-7
CFLAGS = -g -O0 -Wall
#CFLAGS = -O0 -Wall
#CFLAGS = -Os -Wno-deprecated-declarations -Wall -Wunused -Wno-format-y2k  -fno-exceptions -fno-strict-aliasing
#PROFILER = -pg
PROFILER =
TARGETS = chunking
LIBRARY = libchunking
#LIBPTHREADS = -lpthreads -framework Cocoa
LIBGC =
SQLITE = -lsqlite3
INCLUDES = 

.PHONY: install uninstall

all: $(TARGETS)

libchunking: $(OBJS) $(HDRS)
	$(CC) -dynamiclib $(PROFILER) $(OBJS) $(LIBGC) $(SQLITE) -o libchunking.dylib

chunking: $(OBJS) $(HDRS)
	$(CC) $(PROFILER) $(OBJS) $(LIBGC) $(SQLITE) -o chunking

clean:
	rm -f $(TARGETS) $(OBJS)

tidy:
	rm -f $(OBJS)

install:
	cp chunking /usr/local/bin/.
	mkdir /usr/local/share/chunking/
	cp ./text/all_partitions_until_41_parts_only_2s_and_3s.txt /usr/local/share/chunking/
	cp ./text/all_COPRIME_partitions_until_120_with_2_distinct_parts.txt /usr/local/share/chunking/
	cp ./text/all_COPRIME_partitions_until_120_with_3_distinct_parts.txt /usr/local/share/chunking/	
	cp ./text/all_COPRIME_partitions_until_120_with_4_distinct_parts.txt /usr/local/share/chunking/
	cp ./text/all_COPRIME_partitions_until_120_with_5_distinct_parts.txt /usr/local/share/chunking/
	cp ./text/resistor.txt /usr/local/share/chunking/
	cp ./text/release.txt /usr/local/share/chunking/
	cp ./text/arch.txt /usr/local/share/chunking/
	cp ./text/catenary.txt /usr/local/share/chunking/
	cp ./text/alternating.txt /usr/local/share/chunking/
	cp ./text/growth.txt /usr/local/share/chunking/
	cp ./text/decrease.txt /usr/local/share/chunking/
	cp ./text/bracelets.txt /usr/local/share/chunking/
	cp rhy.db /usr/local/share/chunking/

uninstall:
	rm /usr/local/bin/chunking
	rm -r /usr/local/share/chunking/

Alea.o: Alea.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

AlgoComp.o: AlgoComp.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

DList.o: DList.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Interpret.o: Interpret.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Main.o: Main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Modul.o: Modul.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

TextIO.o: TextIO.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Power.o: Power.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Visitor.o: Visitor.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Farey.o: Farey.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

FareyVisitor.o: FareyVisitor.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Ratio.o: Ratio.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

FareyFilter.o: FareyFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

FareyFilterFarey.o: FareyFilterFarey.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

SmoothFilter.o: SmoothFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

ProbFilter.o: ProbFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

OffbeatFilter.o: OffbeatFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

PrimeFilter.o: PrimeFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

SternBrocot.o: SternBrocot.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

ReciprocalFilter.o: ReciprocalFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

SubdivisionFilter.o: SubdivisionFilter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

Christoffel.o: Christoffel.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.cpp)





