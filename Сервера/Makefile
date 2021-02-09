all: Server

Server: main.o TCPServer.o UDPServer.o CreateTCPServerSocket.o CreateUDPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o DieWithError.o        Processing_reqest.o razbivka.o create_json.o
		 	gcc  -pthread main.o TCPServer.o UDPServer.o CreateTCPServerSocket.o CreateUDPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o DieWithError.o        Processing_reqest.o razbivka.o create_json.o -o server -L../lib/json-c -ljson-c -Wl,-rpath,../lib/json-s -std=c99 

DieWithError.o: DieWithError.c
			gcc -c -Wall DieWithError.c -std=c99
	
main.o: main.c
			gcc -c -Wall main.c -std=c99

CreateTCPServerSocket.o: CreateTCPServerSocket.c
			gcc -c -Wall CreateTCPServerSocket.c -std=c99

CreateUDPServerSocket.o: CreateUDPServerSocket.c
			gcc -c -Wall CreateUDPServerSocket.c -std=c99

AcceptTCPConnection.o: AcceptTCPConnection.c
			gcc -c -Wall AcceptTCPConnection.c -std=c99

HandleTCPClient.o: HandleTCPClient.c
			gcc -c -Wall HandleTCPClient.c -std=c99
	
TCPServer.o: TCPServer.c
			gcc -c -Wall TCPServer.c -std=c99
	
UDPServer.o: UDPServer.c
			gcc -c -Wall UDPServer.c -std=c99

Processing_reqest.o: Processing_reqest.c
			gcc -c -Wall Processing_reqest.c -std=c99
	
razbivka.o: razbivka.c
			gcc -c -Wall razbivka.c -std=c99
	
create_json.o: create_json.c
			gcc -c -Wall create_json.c -std=c99		
			

clean: 
	rm -rf *.o server
	
	
	
	
	
