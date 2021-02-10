#include "Server.h"
#define lenght 20
struct
{
  pthread_mutex_t mutex;
} shared = {PTHREAD_MUTEX_INITIALIZER};



char *Processing_request(char *reqest)
{

  struct json_object *for_record;
  struct json_object *string;
  char filename[lenght];
  int j = strlen(reqest);
  for_record = json_object_new_object();
  pthread_mutex_lock(&shared.mutex);
  for (int i = 0; i < j; i++, reqest++)
  {
    if (strncmp(reqest, "1", 1) == 0)
    {

      strcpy(filename, "RAM.txt");
      system("free -h | column -t |tr ',' '.'| tr -s '\t ' ';'  > RAM.txt");
      string = converter(filename);
      json_object_object_add(for_record, filename, string);
    }

    if (strncmp(reqest, "2", 1) == 0)
    {
      strcpy(filename, "Loadavg.txt");
      system("echo loadavg  > Loadavg.txt");
      system("cat /proc/loadavg | tr ' ' ';'| cut -d';' -f1-3  >> Loadavg.txt"); // Загрузка процессора
      string = converter(filename);
      json_object_object_add(for_record, filename, string);
    }

    if (strncmp(reqest, "3", 1) == 0)
    {
      strcpy(filename, "HARD.txt");
      system("df -h |tr ',' '.'| tr -s '\t ' ';'|cut -d ';' -f 1-6 > HARD.txt");
      string = converter(filename);
      json_object_object_add(for_record, filename, string);
    }

    if (strncmp(reqest, "4", 1) == 0)
    {
      strcpy(filename, "Interface.txt");
      system("cat /proc/net/dev | column -t | sed '1d' | cut -d' ' -f1 | sed 's/face/Interface/'| tr -s '\n' ';' > Interface.txt");
      string = converter(filename);
      json_object_object_add(for_record, filename, string);
    }
  }
  pthread_mutex_unlock(&shared.mutex);
    size_t size = strlen(json_object_get_string(for_record)); 
    char *answer;                                          
    answer = (char *)malloc((size + 1) * sizeof(char));
    strcpy(answer, json_object_get_string(for_record)); 
  return answer;
}