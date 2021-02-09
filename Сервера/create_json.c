#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "../lib/json-c/json.h"

char *create_json(char ***str, int stroki, int slova, int len, int slov_v_zagolovke, char *pathname)
{
    int k = 0;
    
    struct json_object *for_record; /* Объект для передачи */
    struct json_object *objects; /* Для создания массива объекта */
    struct json_object *object; /* Для создания обычного объекта */
    struct json_object *parametr; /* Для создания объектной строки */
    objects = json_object_new_array(); /* Создаю массив объектов */
    for_record = json_object_new_object(); /* Создаю объект для записи ключа и массива оъектов */
    if (strncmp(pathname, "HARD", 4) == 0) /* По флагу понимаю какие данные у меня будут */
    {   
        for (int i = 1; i < stroki-1; i++)
        {
            object = json_object_new_object(); /* создаю объект для записи в массив объектов */
            for (int j = 0; j < slov_v_zagolovke; j++)
            {

                parametr = json_object_new_string(str[i][j]); /* Создаю объектную строку и передаю ей значение */
                json_object_object_add(object, str[0][j], parametr); /* Созадю объект с ключом и значением */
            }
            json_object_array_add(objects, object); /* Добавляю получившийся объект в массив объектов */
        }
    }

    if ((strncmp(pathname, "Interface", 9) == 0) || (strncmp(pathname, "Loadavg", 7) == 0))
    {
        if ((strncmp(pathname, "Loadavg", 7) == 0))
            k = 3;
        else
            k = 1;
        for (int i = 1; i < stroki - 1; i++)
        {
            for (int j = 0; j < k; j++)
            {
                parametr = json_object_new_string(str[i][j]); /* Создаю объектную строку и передаю ей значение */
                json_object_array_add(objects, parametr); /* Добавляю получившийся объект в массив объектов */
            }
        }
    }
    if (strncmp(pathname, "RAM", 3) == 0)
    {
        for (int i = 1; i < stroki-1; i++)
        {
            object = json_object_new_object(); /* Создаю объект */
            parametr = json_object_new_string(str[i][0]); /* Создаю объектную строку и передаю ей значение */
            json_object_object_add(object, "Раздел", parametr); /*Создаю первый объект так, потому что в моей таблице его нет, 
                                                                                                а доступ к объектам иметь надо*/
            for (int j = 1; j <= slov_v_zagolovke; j++)
            {
                parametr = json_object_new_string(str[i][j]); /* Создаю объектную строку и передаю ей значение */
                json_object_object_add(object, str[0][j - 1], parametr);/* Созадю объект с ключом и значением */
            }
            json_object_array_add(objects, object); /* Добавляю получившийся объект в массив объектов */
        }
    }
    json_object_object_add(for_record, pathname, objects);  /* Добавлю массив объектов с ключом в финальный объект */
    size_t size = strlen(json_object_get_string(for_record)); /* Вычисляю длину получившейся строки */
    char * answer;                                          /* Создаю строку для последующей ее отправки клиенту */
    answer = (char*)malloc((size+1)*sizeof(char));
    strcpy(answer, json_object_get_string(for_record));     /*Копирую JSON в строку*/
    answer[0] = ' ';                                        /*Удаляю {} для возможности склеивания в одну строку*/
    answer[strlen(answer)-1] = ' ';
    json_object_put(for_record);                            /*Освобождаю объект*/
    return answer;
}
