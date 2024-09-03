pairsofwords: main.o hash.o list.o arr.o CheckErrors.o getWord.o crc64.o
	gcc -o pairsofwords main.o hash.o list.o arr.o CheckErrors.o getWord.o crc64.o

main.o: main.c arr.h hash.h list.h CheckErrors.h getWord.h
	gcc -c main.c

hash.o: hash.c hash.h list.h crc64.h
	gcc -c hash.c

list.o: list.c list.h
	gcc -c list.c

arr.o: arr.c arr.h hash.h list.h
	gcc -c arr.c

CheckErrors.o: CheckErrors.c CheckErrors.h
	gcc -c CheckErrors.c

getWord.o: getWord.c getWord.h
	gcc -c getWord.c

crc64.o: crc64.c crc64.h
	gcc -c crc64.c

clean:
	rm -f pairsofwords main.o hash.o list.o arr.o CheckErrors.o getWord.o crc64.o

