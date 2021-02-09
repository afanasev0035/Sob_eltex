#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <string.h>     


void DieWithError(char *errorMessage);  

int CreateUDPServerSocket(unsigned short port) /* Функция для создания сокета сервера */
{
    int sock;   /* Будущий дескриптор сокета сервера */                      
    struct sockaddr_in ServAddr; /* Структура адреса сервера */
    
    /* Create socket for incoming connections */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) /* Создаю дескриптор сокета */
        DieWithError("socket() failed");
      
    /* Формирую структуру адреса сервера */
    memset(&ServAddr, 0, sizeof(ServAddr));   /* Заполняю ее нулями */
    ServAddr.sin_family = AF_INET;                /* Зануляю структуру */
    ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Выбираю любой интерфейс */
    ServAddr.sin_port = htons(port);              /* Указываю порт */

    /* Связываюсь с локальным адресом */
    if (bind(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
        DieWithError("bind() failed");

    return sock; /* Возвращаю сокет */
}
