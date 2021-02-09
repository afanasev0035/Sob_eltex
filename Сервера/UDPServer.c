#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <pthread.h>     
#include <stdbool.h>
#define SIZEBUFFER 100  /* Первоначальный размер строки запроса */  

char *Processing_request(char *reqest); /* Функция для формирования ответа на запрос */
int CreateUDPServerSocket(unsigned short port); /* Функция для формирования сокета */
void DieWithError(char *errorMessage); 
struct ThreadArgs
{
    int clntPort;
    bool *busy;
};
void *ThreadMainUDP(void *threadArgs); /* Функция потока */
void UDPserver(int port, int man)
{
    int sock;                           /* Сокет сервера */
    struct sockaddr_in ClntAddr;        /* Адрес клиента */
    unsigned int cliAddrLen;            /* Длина структуры адреса клиента */
    char connectBuffer[SIZEBUFFER];     /* Буфер использущийся для соединения */
    int *ServPort;                  /* Порты серверов */
    pthread_t threadID;                 /* ID потока*/
    struct ThreadArgs *threadArgs;      /* Структура для передачи данных в поток */
    bool *busy;                         /* Массив флагов, для понимания есть ли свободные места на сервере */
    char errorMSG[SIZEBUFFER];     /* Сообщение о заполненности сервера */
    strcpy(errorMSG, "Сервер занят, попробуйте позднее");

    
    
    ServPort = (int*)malloc((man + 1) * sizeof(int)); /*Создаю массива портов сервера*/
    ServPort[0] = port; /* Значение порта сервера */
    busy = (bool*)malloc((man + 1) * sizeof(bool));
     
    sock = CreateUDPServerSocket(ServPort[0]); /* Создаю сокет серверу */

    for (;;) 
    {
        /* Задаю занчение длины адреса клиента */
        cliAddrLen = sizeof(ClntAddr);
        /* Читаю сообщение клиента */
        if ((recvfrom(sock, connectBuffer, SIZEBUFFER, 0,
                                    (struct sockaddr *)&ClntAddr, &cliAddrLen)) < 0)
            DieWithError("recvfrom() failed");     
        /* Если сообщение connect */
        if (strcmp(connectBuffer, "connect") == 0)
        {
            for (int score = 1; score < (man + 1); score++)
            {
                if (busy[score]) {}  /* Смотрю есть ли у меня свободные места */
                else{
                    busy[score] = true; /* Если есть, то сразу устанавливаю флаг занято */
                    ServPort[score] = ServPort[0] + score; /* Формирую порт для подключения клиента */
                    /* Формирую струтуру для передачи в поток */
                    if ((threadArgs = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs))) == NULL) 
                        DieWithError("malloc() failed");
                    threadArgs -> clntPort = ServPort[score]; /* Передаю порт сервера */
                    threadArgs -> busy = &busy[score];        /* Указываю адрес флажка, чтобы в конце обозначить что связь с клиенто окончена */    
                    if (pthread_create(&threadID, NULL, ThreadMainUDP, (void *)threadArgs) != 0) /* Создаю поток */
                        DieWithError("pthread_create() failed");
                    char port[6] = {};                             /* Преобразую строку для передачи порта клиенту */
                    snprintf(port, 6, "%u", ServPort[score]);      /* Преобразую число в строку */
                    if (sendto(sock, port, sizeof(port), 0,        /* Отправляю порт клиенту */
                               (struct sockaddr *)&ClntAddr, sizeof(ClntAddr)) < 0)
                        DieWithError("sendto() sending failed");
                    break;
                }
                if ((busy[score]) && (score == man))    /* Если мест нет то сообщаю об этом клиенту */
                {
                if (sendto(sock, errorMSG, sizeof(errorMSG), 0,
                               (struct sockaddr *)&ClntAddr, sizeof(ClntAddr)) < 0)
                    DieWithError("send() failed");
                break;
                }
            }
        }      
    }
    
}

void *ThreadMainUDP(void *threadArgs)
{   
    unsigned short port; /* Номер порта */
    bool *bu;           /* Адрес флага для обозначения когда общение клиент-сервер прекратиться */
    int sock;           /* Сокет потока*/
    char reqestString[SIZEBUFFER]; /* Строка для записи запроса */
    char *answerString;            /* Строка ответа на запрос */
    struct sockaddr_in ClntAddr; /* Структура адреса клиента */
    unsigned int cliAddrLen;     /* Для записи длины структуры адреса клиента */
    int sizeSentMsg = 0;         /* Для записи длины ответа на запрос клиента */
    pthread_detach(pthread_self());  /* Отсоединяю поток */
    port = ((struct ThreadArgs *) threadArgs) -> clntPort; /* Вытаскиваю из струтуры порт для создания сокета */
    bu = ((struct ThreadArgs *) threadArgs) -> busy;        /*Забираю адрес флага что б потом указать что клиент покинул сервер*/
    free(threadArgs); /* Освобождаю структуру */
    sock = CreateUDPServerSocket(port); /* Создаю сокет для общения с клиентом */ 
    cliAddrLen = sizeof(ClntAddr);      /* Записываю длину структуры адреса клиента */
    /* Считываю запрос клиента */
    if (recvfrom(sock,reqestString, SIZEBUFFER, 0, (struct sockaddr *)&ClntAddr, &cliAddrLen) < 0)
        DieWithError("recvfrom() failed"); 
    /* Отправляю запрос функции которая формирует на него ответ */      
    answerString = Processing_request(reqestString); 
    /* Записываю длину полученного ответа */
        sizeSentMsg = strlen(answerString);
        strcpy(reqestString, " "); /*Очищаю строку запроса*/
        sprintf(reqestString, "%d", sizeSentMsg); /* Преобразовываю число в строку */
        /* Отправляю сообщение клиенту, с указанной длинной ответа на запрос */
    if (sendto(sock, reqestString, SIZEBUFFER, 0,
                               (struct sockaddr *)&ClntAddr, sizeof(ClntAddr)) != SIZEBUFFER)
                        {DieWithError("sendto() sending size msg failed");}
        /* Отправляю клиенту ответ на его запрос */
    if (sendto(sock, answerString, sizeSentMsg, 0,
                               (struct sockaddr *)&ClntAddr, sizeof(ClntAddr)) != sizeSentMsg)
                        {DieWithError("sendto() sending msg failed");}
    free(answerString); /* Освобождаю строку ответа */
    *bu = false;    /* Меняю флаг на свободно */
    close(sock);    /* Закрываю сокет */
    return (NULL);
}
