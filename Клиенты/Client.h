#include <stdio.h> 
#include <stdlib.h>   
#include "../lib/json-c/json.h"  
#include <string.h>     
#include <unistd.h>  
#include <sys/socket.h> 
#include <arpa/inet.h> 

void DieWithError(char *errorMessage); /* Оброботчик ошибок */
void parser(char *buffer); /* Функция для расшивровки JSON ответа */
void TCPclient(unsigned int port, char *address, char *reqest); /*Функция запуска TCP клиента*/
void UDPclient(unsigned int ServPort, char *servIP, char *reqest); /*Функция запуска UDP клиента*/
