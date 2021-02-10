#include "Client.h"    
#define len 20
#define SIZEBUFFER 100  /* Первоначальный размер строки запроса */


void TCPclient(unsigned int ServPort, char *servIP, char *reqest)
{
    int sock;                        /* Сокет клиента */
    struct sockaddr_in ServAddr;     /* Структура адреса сервера */
    char *reqestString;              /* Строка запроса */
    size_t size_buffer;              /* Для записи размера ответа, который будет помещен в буффер */
    reqestString = (char *)malloc(SIZEBUFFER * sizeof(char)); /* Формирую начальную строку запроса */
    
   
    strcpy(reqestString, reqest);       /* Строка запроса */
       
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) /* Создаю сокет клиента */
        DieWithError("socket() failed");

                                                        /* Формирую структуру адреса сервера */
    memset(&ServAddr, 0, sizeof(ServAddr));             /* Зануляю структуру 0 */
    ServAddr.sin_family = AF_INET;                      /* Указываю передачу по интернету */
    ServAddr.sin_addr.s_addr = inet_addr(servIP);       /* Указываю IP адрес сервера */
    ServAddr.sin_port = htons(ServPort);                /* Указываю порт сервера */

    /* Устанавливаю соединение с сервером */
    if (connect(sock, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0)
        DieWithError("connect() failed");

    

    /* Отправляю серверу свой запрос */
    if (send(sock, reqestString, sizeof(reqestString), 0) != sizeof(reqestString))
        DieWithError("send() sent a different number of bytes than expected");

    /* Читаю сообщение полученное от сервера */

    if (recv(sock, reqestString, SIZEBUFFER - 1, 0) <= 0)
        DieWithError("recv() failed read size");
    if (strncmp(reqestString, "Сервер занят, попробуйте позднее", 61) == 0)   /* Если получаю сообщение что сервер занят */
    {
        printf("Сервер заполнен, попробуйте позднее\n");                      /* Сообщаю клиенту что сервер заполнен */
        free(reqestString);                                                   /* Освобождаю строку запроса */
        close(sock);                                                          /* Закрываю сокет */
        exit(-1);
    }                                                                         /* Если нет то получаю длину ответа */
    size_buffer = atoi(reqestString);                                         /* Перевожу в число в целочисленное значение */
    reqestString = (char *)realloc(reqestString, (size_buffer + 2) * sizeof(char)); /* Готовлю строку */

    
    if ((recv(sock, reqestString, size_buffer, 0)) <= 0)    /* Читаю строку */
        DieWithError("recv() failed read msg");
    parser(reqestString);                                   /* Расшифровываю JSON сообщение */
    free(reqestString);                                     /* Освобождаю строку */
    printf("\n"); 

    close(sock);                                            /* Закрываю сокет */
    exit(0);
}
