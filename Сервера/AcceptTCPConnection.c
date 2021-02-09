#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  

void DieWithError(char *errorMessage);  

int AcceptTCPConnection(int servSock)
{
    int clntSock;                    /* Сокет клиента */
    struct sockaddr_in ClntAddr; /* Структура адрес клиента */
    unsigned int clntLen;            /* Длина структуры адреса клиента */

    /* Записываю длину структуры адреса клиента */
    clntLen = sizeof(ClntAddr);
    
    /* Жду клиента для соединения */
    if ((clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, 
           &clntLen)) < 0)
        DieWithError("accept() failed");
    
    return clntSock; /* Возвращвю сокет клиента */
}
