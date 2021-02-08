#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#define lenght 20
struct
{
  pthread_mutex_t mutex;
} shared = {PTHREAD_MUTEX_INITIALIZER};

void parser(char *buffer);
char *converter(char *pathname);           /* Ф-ия дробящая файл в массив слов */
char *format(char *answer, char *filename) /* Ф-ия получающа JSON ответ и клеющая его в одну строку */
{
  char *process;                                        /* Будущая строка ответа на запрос */
  int len;                                              /* Дина строки для склейки нескольких ответов */
  process = converter(filename);                        /* Из этой функции получаем JSON ответ на один из вариантов запроса */
  pthread_mutex_unlock (&shared.mutex);                 /*C файлом работа окночена снимаю ограничения*/                                       
  len = strlen(process) + strlen(answer) + 2;           /* Считаем какой длины строка нам потребуется */
  answer = (char *)realloc(answer, len * sizeof(char)); /* Создаем нужную нам строку */
  strncat(answer, process, (len - 2));                  /* Вставляем в выходную строку полученный ответ запрос */
  answer[len - 3] = ',';                                /* Вставляем запятую для приклеки нового сообщения*/
  answer[len - 2] = '\0';                               /* Указываем конец строки*/
  free(process);                                        /* Освобождаю строку ответа на запрос */
  return answer;                                        /* возвращаю склеенную строку */
}

char *Processing_request(char *reqest)
{

  char *answer;
  char filename[lenght];                          /* Создаю строку для записи имени файла, для последующе передачи ее в converter */
  answer = (char *)malloc(lenght * sizeof(char)); /* Создаю выходную строку для полседующей передачи ее клиенту */
  strcpy(answer, "{");                            /* Открываю JSON запрос */
  int j = strlen(reqest);                         /* Определяю длину reqest */
  for (int i = 0; i < j; i++, reqest++)
  {
    if (strncmp(reqest, "1", 1) == 0) /* По маркерам определяю какой ответ хотят услышать от сервера */
    {
      pthread_mutex_lock (&shared.mutex);                                      /* Так как работаю с файлом, ставлю мютекс, чтобы другие потоки не испортили его*/
      strcpy(filename, "RAM.txt");                                           /* Записываю в строку имя файла где будет лежать таблица с нужными параметрами */
      system("free -h | column -t |tr ',' '.'| tr -s '\t ' ';'  > RAM.txt"); /* Получаю информацию из системы и записываю ее в файл */
      answer = format(answer, filename);                                     /* Отправляю конечную строку и имя файла в ф-ию format */
      pthread_mutex_unlock (&shared.mutex);                               
    }

    if (strncmp(reqest, "2", 1) == 0)
    {
      pthread_mutex_lock (&shared.mutex);
      strcpy(filename, "Loadavg.txt");
      system("echo loadavg  > Loadavg.txt");
      system("cat /proc/loadavg | tr ' ' ';'| cut -d';' -f1-3  >> Loadavg.txt"); // Загрузка процессора
      answer = format(answer, filename);
      
    }

    if (strncmp(reqest, "3", 1) == 0)
    {
       pthread_mutex_lock (&shared.mutex);
      strcpy(filename, "HARD.txt");
      system("df -h |tr ',' '.'| tr -s '\t ' ';'|cut -d ';' -f 1-6 > HARD.txt");
      answer = format(answer, filename);
    }

    if (strncmp(reqest, "4", 1) == 0)
    {
      pthread_mutex_lock (&shared.mutex);
      strcpy(filename, "Interface.txt");
      system("cat /proc/net/dev | column -t | sed '1d' | cut -d' ' -f1 | sed 's/face/Interface/' > Interface.txt");
      answer = format(answer, filename);
    }
  }

  answer[strlen(answer) - 1] = '}'; /* Закрываю JSON запрос */
  answer[strlen(answer)] = '\0';    /* Указываю конец строки */
  return answer;                    /* Возвращаю JSON ответ */
}
