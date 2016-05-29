#stole some of this from Dr Norris's make file.
CC=g++
CFLAGS=-g -L/usr/local/lib -I/usr/local/include
LDFLAGS=-lrdkafka++
OBJS=data.o publish.o

.C.o:
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@
kafka-producer: $(OBJS)

data.o: data.h

publish.o: publish.h

test.o: publish.h 

test: test.o publish.o
	$(CC) $(CFLAGS) $(LDFLAGS) publish.o test.o -o test


clean:
	rm *.o kafka-producer
