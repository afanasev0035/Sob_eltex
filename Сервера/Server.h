#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <pthread.h>     
#include <stdbool.h>
#include <malloc.h>
#include "../lib/json-c/json.h"
void DieWithError(char *errorMessage);  /* Error handling function */
void HandleTCPClient(int clntSocket);   /* TCP client handling function */
int CreateTCPServerSocket(unsigned short port, int man); /* Create TCP server socket */
int AcceptTCPConnection(int servSock);  /* Accept TCP connection request */
void *ThreadMainTCP(void *arg); /* Программа потока */
char *Processing_request(char *reqest); /* Функция для формирования ответа на запрос */
int CreateUDPServerSocket(unsigned short port); /* Функция для формирования сокета */
void copy_word(char *a, char *string_for_copy, int n_1, int n_2);
json_object *converter(char *pathname);
