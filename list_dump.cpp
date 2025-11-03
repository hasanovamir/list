/*
    AI generated 
    for reference only
*/

#include "list.h"

//--------------------------------------------------------------------------------

list_err_t FillDotFile (list_t* list, const char* file_name)
{
    DEBUG_ASSERT (list      != NULL);
    DEBUG_ASSERT (file_name != NULL);

    FILE* dot_file = fopen (file_name, "w");
    
    if (dot_file == NULL)
    {
        PRINTERR (LIST_OPEN_FILE_ERR);
        return   (LIST_OPEN_FILE_ERR);
    }

    

    fclose(dot_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListDump (list_t* list, const char* file_name)
{
    DEBUG_ASSERT (list      != NULL);
    DEBUG_ASSERT (file_name != NULL);

    char dot_file_name[100];
    char png_file_name[100];
    char command[100];
    
    snprintf(dot_file_name, sizeof(dot_file_name), "%s.dot", file_name);
    snprintf(png_file_name, sizeof(png_file_name), "%s.png", file_name);
    
    if (FillDotFile(list, dot_file_name))
        return LIST_OPEN_FILE_ERR;

    printf("Generated DOT file: %s\n", dot_file_name);
    
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_file_name, png_file_name);

    int result = system(command);
    
    if (result == 0)
    {
        printf("Generated PNG image: %s\n", png_file_name);
        return LIST_SUCCESS;
    }
    else
    {
        PRINTERR (LIST_SYS_FUNC_ERR);
        return LIST_SYS_FUNC_ERR;
    }
}

//--------------------------------------------------------------------------------

void ListTerminalDump (list_t* list)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    list_data_t* data_arr = list->data;
    int*         next_arr = list->next;
    int*         prev_arr = list->prev; 

    printf ("  | data | next | prev |\n");

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] == POISON)
        {
            printf ("%2d|POISON|%6d|%6d|\n", i, next_arr[i], prev_arr[i]);
        }
        else
        {
            printf ("%2d|%6d|%6d|%6d|\n", i, data_arr[i], next_arr[i], prev_arr[i]);
        }
    }

    printf ("|free = %d|capacity = %d|\n|head = %d|\n|tail = %d|\n", list->free, list->capacity, list->head, list->tail);
}

//--------------------------------------------------------------------------------