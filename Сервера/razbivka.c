#include "Server.h"
#define len 100



json_object *converter(char *pathname)
{
    char zagolovok[len][len];
    int x = 0;
    FILE *fp;                       /* Будущий файл с данными */
    struct json_object *objects;    /* Для создания массива объекта */
    struct json_object *object;     /* Для создания обычного объекта */
    struct json_object *parametr;   /* Для создания объектной строки */
    objects = json_object_new_array();
    /* Открытие файла */
    if ((fp = fopen(pathname, "r")) == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    /* Чтение файла в массив строк */
    while (!feof(fp))
    {
        char string[BUFSIZ];       /* Для записи строк из файла */
        fgets(string, BUFSIZ, fp); /* Получаю строку из файла */
        int zap_1 = 0;             /* Позиция разделителя в строке перед словом */
        int zap_2 = 0;             /* Позиция разделителя в строке после слова */
        char word[len];
        if (x == 0)
        {
            for (int i = 0; i < strlen(string); i++)
            {
                if ((string[i] == ';') || (string[i] == '\n'))
                {
                    zap_1 = zap_2;
                    zap_2 = i;
                    copy_word(zagolovok[x], string, zap_1, zap_2);
                    x++;
                }
            }
        }
        else
        {
            x = 0;
            object = json_object_new_object();
            for (int i = 0; i < strlen(string); i++)
            {
                if ((string[i] == ';') || (string[i] == '\n'))
                {
                    zap_1 = zap_2;
                    zap_2 = i;
                    copy_word(word, string, zap_1, zap_2);
                    parametr = json_object_new_string(word);
                    if (strncmp(pathname, "HARD", 4) == 0)
                    {
                        json_object_object_add(object, zagolovok[x], parametr);
                        x++;
                    }
                    else if (strncmp(pathname, "RAM", 3) == 0)
                    {
                        if (x == 0)
                            json_object_object_add(object, "Параметр", parametr);
                        else
                            json_object_object_add(object, zagolovok[x - 1], parametr);
                        x++;
                    }
                }
            }
            json_object_array_add(objects, object);
        }
    }
    json_object_array_del_idx(objects, json_object_array_length(objects) - 1, 1);
    /* Закрываю файл */
    fclose(fp);
    remove(pathname);
    if ((strncmp(pathname, "Interface", 9) == 0) || (strncmp(pathname, "Loadavg", 7) == 0))
    {
        objects = json_object_new_array();
        for (int i = 0; i < x; i++)
        {

            parametr = json_object_new_string(zagolovok[i]);
            json_object_array_add(objects, parametr);
        }
    }

  
    return objects;
}

void copy_word(char *a, char *string_for_copy, int n_1, int n_2)
{
    if (n_1 != 0)
        n_1++;
    strcpy(a, ""); /* Очищаю строку */
    for (int i = n_1; i < n_2; i++)
    {
        a[i - n_1] = string_for_copy[i]; /* Копирую слово */
        a[i - n_1 + 1] = '\0';           /* Указываю конец строки */
    }
}
