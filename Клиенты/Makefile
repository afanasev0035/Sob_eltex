all: main

main: DieWithError.o main.o parser.o TCPclient.o UDPclient.o
		gcc -Wall DieWithError.o main.o parser.o TCPclient.o UDPclient.o -o client -std=c99  -L../lib/json-c -ljson-c -Wl,-rpath,../lib/json-s

DieWithError: DieWithError.c
		gcc -c -Wall DieWithError.c -std=c99
	
main.o: main.c
		gcc -c -Wall main.c -std=c99

parser.o: parser.c
		gcc -c -Wall parser.c -std=c99
	
TCPclient.o: TCPclient.c
		gcc -c -Wall TCPclient.c -std=c99
	
UDPclient.o: UDPclient.c
		gcc -c -Wall UDPclient.c -std=c99

clean: 
	rm -rf *.o client
