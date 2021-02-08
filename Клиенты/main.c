#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define len 20
void TCPclient(unsigned int port, char *address, char *reqest);
void UDPclient(unsigned int port, char *address, char *reqest);
int main()
{
    int protocol;
    char address[len];
    unsigned int port;
    char reqest[len];
    printf("Выберите типа соединения 1 - TCP; 2 - UDP \n");
    scanf("%d", &protocol);
    getchar();
    printf("Укажите адрес сервера \n");
    fgets(address, len, stdin);
    printf("Укажите порт сервера \n");
    scanf("%d", &port);
    getchar();
    printf("В программе реализованы следующие запросы\n");
    printf("1 - Состояние RAM\n");
    printf("2 - Текаущая загрузка ЦП\n");
    printf("3 - Состояние и свободное место на дисках\n");
    printf("4 - Список интерфейсоф\n");
    fgets(reqest, len, stdin);
  
    

    if (protocol == 1)
    {
        TCPclient(port, address, reqest);
    }
    else if (protocol == 2)
    {
        UDPclient(port, address, reqest);
    }
    else
        printf("Протокол выбран не корректно\n");
}