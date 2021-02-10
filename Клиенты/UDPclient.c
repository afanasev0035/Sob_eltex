#include "Client.h"
#define SIZEBUFFER 100  /* Первоначальный размер строки запроса */    

void UDPclient(unsigned int ServPort, char *servIP, char *reqest)
{
    int sock;                        /* Сокет клиента */
    struct sockaddr_in ServAddr;     /* Структура адреса сервера */
    struct sockaddr_in fromAddr;     /* Структура адреса клиента */
    unsigned int fromSize;           /* Длина струтуры сервера */
    char *reqestString;              /* Строка запроса */
    size_t size_buffer;              /* Для записи размера ответа, который будет помещен в буффер */
    char connectBuffer[SIZEBUFFER];              /* Буфер для хранения сообщения с просьбой о соединении */
    reqestString = (char*)malloc(SIZEBUFFER * sizeof(char));

   
    strcpy(connectBuffer, "connect");
    strcpy(reqestString, reqest);       /* Строка запроса */
        

    /* Создаю сокет UDP для клиента */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    /* Создаю структуру адреса сервера */
    memset(&ServAddr, 0, sizeof(ServAddr));         /* Зануляю структуру 0 */
    ServAddr.sin_family = AF_INET;                  /* Указываю передачу по интернету */
    ServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Указываю IP адрес сервера */
    ServAddr.sin_port   = htons(ServPort);          /* Указываю порт сервера */

    /* Отправляю сообщение с просьюой о выделении отдельного порта */
    if (sendto(sock, connectBuffer, sizeof(connectBuffer), 0, (struct sockaddr *)
               &ServAddr, sizeof(ServAddr)) != sizeof(connectBuffer))
        DieWithError("sendto() sent a different number of bytes than expected");
    fromSize = sizeof(fromAddr);
    /* Читаю сообщение из сокета */
    if (recvfrom(sock, connectBuffer, SIZEBUFFER, 0, 
         (struct sockaddr *) &fromAddr, &fromSize) < 0)
        DieWithError("recvfrom() failed");
    /* Проверяю с того ли адреса оно вернулось */
    if (ServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr,"Error: received a packet from unknown source.\n");  /* Если с другого то завершаю работу */
        free(reqestString);                                                 /* Освобождаю строку запроса */
        close(sock);                                                        /* Закрываю сокет */
        exit(1);
    }
    /* Проверяю содержание сообщения */
    if (strncmp(connectBuffer, "Сервер занят, попробуйте позднее", 61) == 0)   /* Если получаю сообщение что сервер занят */
    {
        printf("Сервер заполнен, попробуйте позднее\n");                      /* Сообщаю клиенту что сервер заполнен */
        free(reqestString);                                                   /* Освобождаю строку запроса */
        close(sock);                                                          /* Закрываю сокет */
        exit(-1);
    }  
    else 
    {   
        ServPort = atoi (connectBuffer);            /* Перевожу полученный порт в целое значение */
        ServAddr.sin_port   = htons(ServPort);     /* Присваиваю структуре адреса сервера новый порт */           
    }
    /* Отправляю запрос серверу */
   if (sendto(sock, reqestString, sizeof(reqestString), 0, (struct sockaddr *)
               &ServAddr, sizeof(ServAddr)) != sizeof(reqestString))
        DieWithError("sendto() sent a different number of bytes than expected");

    /* Считываю какая будет длина ответа на мой запрос */
    fromSize = sizeof(fromAddr);
    if ((recvfrom(sock, reqestString, SIZEBUFFER - 1, 0, 
         (struct sockaddr *) &fromAddr, &fromSize)) < 0)
        DieWithError("recvfrom() failed");
    if (ServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr,"Error: received a packet from unknown source.\n");  /* Если с другого то завершаю работу */
        free(reqestString);                                                 /* Освобождаю строку запроса */
        close(sock);                                                        /* Закрываю сокет */
        exit(1);
    }

    size_buffer = atoi(reqestString);                                       /* Преобразую длину в целое число */
    char *answer = (char*)malloc((size_buffer + 1) * sizeof(char));         /* Готовлю массив */
    /*Считываю ответ на запрос*/
    fromSize = sizeof(fromAddr);
    if (recvfrom(sock, answer, size_buffer, 0,             
         (struct sockaddr *) &fromAddr, &fromSize) < size_buffer)
        DieWithError("recvfrom() failed");
    answer[size_buffer + 1] = '\0';         /*Добавляю в конец обозначение конец строки*/
    parser(answer);
    close(sock);
    exit(0);
}