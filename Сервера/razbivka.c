#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


char *create_json(char ***str, int stroki, int slova, int len, int slov_v_zagolovke, char *pathname);
void copy_word(char *string_to_copy, char *string_for_copy, int n_1, int n_2);

char *converter(char *pathname)
{

    FILE *fp; /* Будущий файл с данными */
    char ***str = NULL; /* Массив со словами из файла */
    int kol_slov = 0; /* конечное кол-во слов */
    int kol_strok = 0;/* Конечное значение кол-ва строк */
    int stroki = 2; /* количество строк в массиве */
    int slova = 2;  /* количество слов в строке массива */
    int len = 20;   /* длина слов в строке массива */ 
    int slov_v_zagolovke = 0; /* Слов в заголовке для понимания сколько будет колонок (объектов) */ 
    
    /* Создание массива строк */
     
    str = (char ***)malloc(stroki * sizeof(char **));
    for (int i = 0; i < stroki; i++)
    {
        str[i] = (char **)malloc(slova * sizeof(char *));
        for (int j = 0; j < slova; j++){
            str[i][j] = (char *)malloc(len * sizeof(char));
            
        }
    }
   
      /* Открытие файла */
     if ((fp = fopen(pathname, "r")) == NULL)
    {   

        
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

   
    
    /* Чтение файла в массив строк */
    while (!feof(fp))
    {
        char string[BUFSIZ]; /* Для записи строк из файла */
        fgets(string, BUFSIZ, fp); /* Получаю строку из файла */
        int zap_1 = 0; /* Позиция разделителя в строке перед словом */
        int zap_2 = 0; /* Позиция разделителя в строке после слова */
    
        /* Проверка хватает ли еще в созданом массиве кол-во строк */
        if (kol_strok >= stroki)
        {   /* Если количество строк не устраивает пересоздаю массив */
            stroki = stroki + 1;
            str = (char ***)realloc(str, stroki * sizeof(char *));
            for (int i = kol_strok; i < stroki; i++)
            {
                str[i] = (char **)malloc(slova * sizeof(char *));
                for (int j = 0; j < slova; j++){
                    str[i][j] = (char *)malloc(len * sizeof(char));
                    strcpy(str[i][j], "");
            }
            }
        }

        /* Ищу ";" для выцепления из строк слов для последующей записи их в массив */
        for (int i = 0; i < strlen(string); i++)
        {
            if ((string[i] == ';') || (i == (strlen(string) - 1)))
            {
                zap_1 = zap_2;
                zap_2 = i;
                /* Проверяю хватит ли мне длины слова в массиве для записи выцепленного слова из файла */
                if ((zap_2 - zap_1) >= len)
                {   /* Если нет переопределяю массив */
                    len = zap_2 - zap_1 + 2;
                    str = (char ***)realloc(str, stroki * sizeof(char *));
                    for (int i = 0; i < stroki; i++)
                    {
                        str[i] = (char **)realloc(str[i], slova * sizeof(char *));
                        for (int j = 0; j < slova; j++)
                            str[i][j] = (char *)realloc(str[i][j], len * sizeof(char));
                    }
                }
                /* Копирую слово в массив */
                copy_word(str[kol_strok][kol_slov], string, zap_1, zap_2);
                kol_slov++;
                /*  Проверяю хватает ли мне слов в строке, для продожения записи слов из текста в массив */
                if (kol_slov >= slova)
                {   /* Если нет переопределяю массив */
                    slova = slova + 1;
                    str = (char ***)realloc(str, stroki * sizeof(char *));
                    for (int i = 0; i < stroki; i++)
                    {
                        str[i] = (char **)realloc(str[i], slova * sizeof(char *));
                        for (int j = kol_slov; j < slova; j++){
                            str[i][j] = (char *)malloc(len * sizeof(char));
                            strcpy(str[i][j], "");
                        }
                    }
                }
            }
        }
        if (kol_strok == 0)
        {
            slov_v_zagolovke = kol_slov; /* Записываю сколько слов в заголовке для понимания сколько будет колонок (объектов) */
        }
        kol_strok++;
        kol_slov = 0;
    }
    /* Закрываю файл */
    fclose(fp);
    remove(pathname); /* Удаляю файл */
    /*Формирую json ответ*/
     
    pathname = create_json(str, stroki, slova, len, slov_v_zagolovke, pathname);
    /* Освобождаю массив из памяти */
    for (int i = 0; i < stroki; i++)
    {
        for (int j = 0; j < slova; j++)
            free(str[i][j]);
        free(str[i]);
    }
    free(str);
    return pathname;
}

void copy_word(char *string_to_copy, char *string_for_copy, int n_1, int n_2)
{
    if (n_1 != 0)
        n_1++;
    strcpy(string_to_copy,""); /* Очищаю строку */
    for (int i = n_1; i < n_2; i++)
    {
        string_to_copy[i - n_1] = string_for_copy[i]; /* Копирую слово */
        string_to_copy[i - n_1 + 1] = '\0';           /* Указываю конец строки */
    }
}