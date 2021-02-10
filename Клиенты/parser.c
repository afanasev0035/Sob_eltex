#include "Client.h"  
void parser(char *buffer)
{

    struct json_object *parsed_json;
    struct json_object *objects;
    struct json_object *object;

    size_t quntity = 0;
    if (strlen(buffer) <= 3)
    {
        printf("Запрос введен не корректно\n");
    }

    parsed_json = json_tokener_parse(buffer);

    //CPU
    json_object_object_get_ex(parsed_json, "Loadavg.txt", &objects);
    if (objects != NULL)
    {

        quntity = json_object_array_length(objects);
        printf("Loadavg: ");

        for (int i = 0; i < quntity; i++)
        {
            object = json_object_array_get_idx(objects, i);
            printf("%8s\t", json_object_get_string(object));
        }
        printf("\n\n");
        objects = NULL;
        object = NULL;
    }

    //HARD
    struct json_object *File_sysytem;
    struct json_object *size;
    struct json_object *using;
    struct json_object *available;
    struct json_object *using_proc;
    struct json_object *mount;

    json_object_object_get_ex(parsed_json, "HARD.txt", &objects);
    if (objects != NULL)
    {
        quntity = json_object_array_length(objects);
        printf("Файл.система\t  Размер\tИспользовано\t    Дост\tИспользовано%%   Cмонтировано\n");

        for (int i = 0; i < quntity; i++)
        {
            object = json_object_array_get_idx(objects, i);
            json_object_object_get_ex(object, "Файл.система", &File_sysytem);
            json_object_object_get_ex(object, "Размер", &size);
            json_object_object_get_ex(object, "Использовано", &using);
            json_object_object_get_ex(object, "Дост", &available);
            json_object_object_get_ex(object, "Использовано%", &using_proc);
            json_object_object_get_ex(object, "Cмонтировано", &mount);
            printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t\n", json_object_get_string(File_sysytem), json_object_get_string(size),
                   json_object_get_string(using), json_object_get_string(available), json_object_get_string(using_proc),
                   json_object_get_string(mount));
        }
        object = NULL;
        objects = NULL;
        printf("\n\n");
    }

    //Interface
    json_object_object_get_ex(parsed_json, "Interface.txt", &objects);
    if (objects != NULL)
    {
        quntity = json_object_array_length(objects);

        for (int i = 0; i < quntity; i++)
        {
            object = json_object_array_get_idx(objects, i);
            printf("%8s\t", json_object_get_string(object));
        }
        object = NULL;
        objects = NULL;
        printf("\n\n");
    }

    //RAM

    struct json_object *name;
    struct json_object *total;
    struct json_object *busy;
    struct json_object *free;
    struct json_object *general;
    struct json_object *buff_tim;

    json_object_object_get_ex(parsed_json, "RAM.txt", &objects);
    if (objects != NULL)
    {
        quntity = json_object_array_length(objects);
        printf("\tвсего\tзанято\tсвободно общая\tбуф./врем. доступно\n");
        for (int i = 0; i < quntity; i++)
        {
            object = json_object_array_get_idx(objects, i);
            json_object_object_get_ex(object, "Параметр", &name);
            json_object_object_get_ex(object, "всего", &total);
            json_object_object_get_ex(object, "занято", &busy);
            json_object_object_get_ex(object, "свободно", &free);
            json_object_object_get_ex(object, "общая", &general);
            json_object_object_get_ex(object, "буф./врем.", &buff_tim);
            json_object_object_get_ex(object, "доступно", &available);
            if (strncmp(json_object_get_string(name), "Подкачка:", 18) == 0)
            printf("%s%s\t%s\t%s\t\n", json_object_get_string(name), json_object_get_string(total), json_object_get_string(busy),
                   json_object_get_string(free));
            else{
            printf("%s%s\t%s\t%s\t%s\t%s\t   %s\n", json_object_get_string(name), json_object_get_string(total), json_object_get_string(busy),
                   json_object_get_string(free), json_object_get_string(general), json_object_get_string(buff_tim), json_object_get_string(available));}
        }
        object = NULL;
        objects = NULL;
        printf("\n\n");
    }

    json_object_put(parsed_json);
}
