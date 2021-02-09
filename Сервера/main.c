#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define len 20
void TCPserver(int port, int man);
void UDPserver(int port, int man);
int main()
{
    
    int port;
    int man;
    int protocol;
    printf("Укажите порт сервера \n");
    scanf("%d", &port);
    printf("Укажите какое кол-во людей может обслуживать сервер \n");
    scanf("%d", &man);
    
    printf("Выберите типа соединения 1 - TCP; 2 - UDP \n");
    scanf("%d", &protocol);

    if (protocol == 1)
    {
        TCPserver(port, man);
    }
    else if (protocol == 2)
    {
        UDPserver(port, man);
    }
    else
        printf("Протокол выбран не корректно\n");
}