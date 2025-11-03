#include "list.h"

//--------------------------------------------------------------------------------

int num_calls = 0;

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

    fprintf(dot_file, "digraph ListDump {\n\trankdir=LR;\n\tnode [shape=Mrecord, fontname=\"Courier\"];\n\n");

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] == POISON)
        {
            if (i == list->free) //poison + free
            {
                fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:PSN | <prev> prev:%d | <next> next:%d\", style=filled, color=aqua];\n", 
                    i, i, list->prev[i], list->next[i]);
            }
            else //just poison
            {
                fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:PSN | <prev> prev:%d | <next> next:%d\", style=filled, color=yellow];\n", 
                    i, i, list->prev[i], list->next[i]);
            }
        }
        else
        {
            if (i == list->head) //head
            {
                fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:%d | <prev> prev:%d | <next> next:%d\", style=filled, color=magenta];\n", 
                    i, i, list->data[i], list->prev[i], list->next[i]);
            }
            else if (i == list->tail) //tail
            {
                fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:%d | <prev> prev:%d | <next> next:%d\", style=filled, color=crimson];\n", 
                    i, i, list->data[i], list->prev[i], list->next[i]);
            }
            else //just filled node
            {
                fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:%d | <prev> prev:%d | <next> next:%d\", style=filled, color=lime];\n", 
                    i, i, list->data[i], list->prev[i], list->next[i]);
            }
        }
    }

    fprintf (dot_file, "\n\tgraph [splines=ortho]\n\toverlap=false;\n\n");

    for (int i = 0; i < list->capacity; i++)
    {
        if (i < list->capacity - 1) // i + 1 < cap // invis node connection
        {
            fprintf (dot_file, "\tnode%d -> node%d [style = invis, weight = 100];\n\tnode%d -> node%d [style = invis, weight = 100];\n", i, i + 1, i, i + 1);
        }

        if (list->data[i] == POISON && i != 0) // free connection
        {
            fprintf(dot_file, "\tnode%d -> node%d [color=purple, constraint=false];\n", i, list->next[i]);
        }
        else // connection of ordinary members
        {
            fprintf(dot_file, "\tnode%d -> node%d [color=blue, constraint=false];\n\tnode%d -> node%d [color=green, constraint=false];\n", i, list->next[i], i, list->prev[i]);
        }
    }
    
    fprintf(dot_file, "}\n");

    fclose(dot_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListDump (list_t* list)
{
    DEBUG_ASSERT (list != NULL);

    num_calls++;

    char dot_file_name[20];
    char png_file_name[20];
    char command[50];
    
    snprintf(dot_file_name, sizeof(dot_file_name), "dot/%s_%d.dot", "call", num_calls);
    snprintf(png_file_name, sizeof(png_file_name), "png/%s_%d.png", "call", num_calls);
    
    if (FillDotFile (list, dot_file_name))
    {
        return LIST_OPEN_FILE_ERR;
    }

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
        return   (LIST_SYS_FUNC_ERR);
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