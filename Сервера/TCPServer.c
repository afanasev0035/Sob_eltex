#include "Server.h" 
#define SIZEBUFFER 100


/* Структура переменных для передачи клиенту в поток */
struct ThreadArgs
{
    int clntSock; /* Сокет клиента */
    bool *busy; /* Флаг глиента, что он находится на сервере */
};



void TCPserver(int port, int man)
{
    int servSock;                  /* Сокет сервера */
    int clntSock;                  /* Сокет клиента */
    unsigned short ServPort;       /* Порт сервера */
    pthread_t threadID;            /* ID для создания потока */
    struct ThreadArgs *threadArgs; /* Структура для передачи данных в поток */
    bool *busy;                    /* Массив флагов для определения кол-во людей на сервере */
    char errorMSG[SIZEBUFFER];     /* Сообщение о заполненности сервера */
    strcpy(errorMSG, "Сервер занят, попробуйте позднее");
 

    ServPort = port;     /* Задаю порт сервера */
    servSock = CreateTCPServerSocket(ServPort, man); /* Создаю сокет сервера */
    busy = (bool*)malloc(man * sizeof(bool)); /* Создаю массив флагов, для понимания есть ли свободные места на сервере */
    for (;;) 
    {
        clntSock = AcceptTCPConnection(servSock); /* Выделяю сокет клиенту */
        for (int score = 0; score < man; score++) /* Поверяю есть ли место на сервере*/
        {
            if (busy[score])
            {
                
            }
            else
            {                         /* Если место есть */
                busy[score] = true;  /* Сигнализираю что место занято */
                /* Создаю структуру для потока */
                if ((threadArgs = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs))) == NULL)
                    DieWithError("malloc() failed");
                threadArgs->clntSock = clntSock; /* Указываю сокет клиента */
                threadArgs->busy = &busy[score]; /* Указываю адрес флажка, чтобы в конце обозначить что связь с клиенто окончена */
                /* Создаю поток */
                if (pthread_create(&threadID, NULL, ThreadMainTCP, (void *)threadArgs) != 0)
                    DieWithError("pthread_create() failed");
                break;
            }
             if ((busy[score]) && (score == (man - 1))) /* Если места нет */
            {   /* Отправляю сообщение о том что сервер заполнен */
                if ((send(clntSock, errorMSG, sizeof(errorMSG), 0)) != sizeof(errorMSG)) 
                    DieWithError("send() failed");
                close(clntSock);                                                         /* Закрываю сокет */
                break;
            }
        }
    }
}

void *ThreadMainTCP(void *threadArgs)
{
    int clntSock; /* Сокет клиента */
    bool *bu; /* Адрес флага для обозначения когда общение клиент-сервер прекратиться */
    /* Отсоединяю поток */
    pthread_detach(pthread_self());
    /* Вытаскиваю из структуры данные */
    clntSock = ((struct ThreadArgs *)threadArgs)->clntSock;
    bu = ((struct ThreadArgs *)threadArgs)->busy;
    free(threadArgs); /* Освобождаю структуру */
    HandleTCPClient(clntSock); /* Начинаю общение с клиентом */
    *bu = false; /* Сигнализирую что общение закончено */
    return (NULL);
}
