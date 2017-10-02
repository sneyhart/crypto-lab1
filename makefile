CC = g++
CFLAGS = -g -Wall
LFLAGS = -g -Wall
OBJS = cbc-enc.o cbc-dec.o ctr-enc.o ctr-dec.o util.o
LIBS =  -lssl -lcrypto 

.suffixes: .c .o

all: cbc-enc cbc-dec ctr-enc ctr-dec $(OBJS)

.c.o: util.h util.o
	$(CC) $(CFLAGS) -c $*.c 
	
cbc-enc: cbc-enc.o util.o util.h
	$(CC) $(LFLAGS) -o $@ $@.o util.o $(LIBS)

cbc-dec: cbc-dec.o util.o util.h
	$(CC) $(LFLAGS) -o $@ $@.o util.o $(LIBS)

ctr-enc: ctr-enc.o util.o util.h
	$(CC) $(LFLAGS) -o $@ $@.o util.o $(LIBS)

ctr-dec: ctr-dec.o util.o util.h
	$(CC) $(LFLAGS) -o $@ $@.o util.o $(LIBS)
    
clean:
	rm *.o cbc-enc cbc-dec ctr-enc ctr-dec 
