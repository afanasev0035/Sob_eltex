#include "Server.h"

#define SIZEBUFFER 100
#define SIZELEN 10


void HandleTCPClient(int clntSocket)
{
    char reqestString [SIZEBUFFER]; /* Строка для записи запроса от клиента */
    char *answerString;             /* Строка для ответа на запрос */
    int recvMsgSize;                /* Размер ответа которое будет передаваться клиенту */

    /* Считываю запрос клиента */
    if ((recvMsgSize = recv(clntSocket, reqestString, SIZEBUFFER, 0)) < 0)
    {
        DieWithError("recv() failed");
    }

    /* Отправляю запрос функции которая формирует на него ответ */
    answerString = Processing_request(reqestString);
    /* Записываю длину полученного ответа */
    recvMsgSize = strlen(answerString);
    /* Создаю массива для записи в него длины сообщения */
    char size[SIZELEN];
    /* Преобразовываю число в строку */
    sprintf(size, "%d", recvMsgSize);
    /* Отправляю сообщение о длине ответа */
    if ((send(clntSocket, size, SIZELEN, 0)) != SIZELEN)
    {
        DieWithError("send() failed");
    }
    /* Отправляю ответ клиенту */
    if (send(clntSocket, answerString, recvMsgSize, 0) != recvMsgSize)
        DieWithError("send() failed");
    free(answerString); /* Освобождаю строку */
    
    close(clntSocket); /* Закрываю сокет */
}
