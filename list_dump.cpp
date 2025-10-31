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

    fprintf(dot_file, "digraph ListDump {\n");

    fprintf(dot_file, "    subgraph cluster_ListInf {\n");
    fprintf(dot_file, "        label=\"List Information\";\n");
    fprintf(dot_file, "        labelloc=t;\n");
    fprintf(dot_file, "        labeljust=l;\n");
    fprintf(dot_file, "        color=blue;\n");
    fprintf(dot_file, "        fontsize=12;\n");
    fprintf(dot_file, "        \n");
    fprintf(dot_file, "        list_node [label=\"Head = %d\\nTail = %d\\nFree = %d\\nCapacity = %d\", \n", list->head, list->tail, list->free, list->capacity);
    fprintf(dot_file, "                   shape=plaintext, fontsize=10];\n");
    fprintf(dot_file, "    }\n\n");

    fprintf(dot_file, "    subgraph cluster_Colours {\n");
    fprintf(dot_file, "        label=\"Colours\";\n");
    fprintf(dot_file, "        labelloc=t;\n");
    fprintf(dot_file, "        labeljust=r;\n");
    fprintf(dot_file, "        color=blue;\n");
    fprintf(dot_file, "        fontsize=12;\n");
    fprintf(dot_file, "        \n");
    fprintf(dot_file, "        colour_node [label=\"BLUE = NEXT\\nGREEN = PREV\\nPURPLE = FREE\", \n");
    fprintf(dot_file, "                   shape=plaintext, fontsize=10];\n");
    fprintf(dot_file, "    }\n\n");

    fprintf(dot_file, "    list_node -> colour_node [style=invis, constraint=false];\n\n");

    fprintf(dot_file, "    rankdir=LR;\n"     );
    fprintf(dot_file, "    node [shape=record, fontname=\"Courier\"];\n\n");

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] == POISON)
            fprintf(dot_file, "    node%d [label=\"<f0> idx:%d | <f1> data:PSN | <f2> prev:%d | <f3> next:%d\"];\n", 
                    i, i, list->prev[i], list->next[i]);
        else
            fprintf(dot_file, "    node%d [label=\"<f0> idx:%d | <f1> data:%d | <f2> prev:%d | <f3> next:%d\"];\n", 
                    i, i, list->data[i], list->prev[i], list->next[i]);    
    }

    for (int i = 0; i < list->capacity - 1; i++)
    {
        fprintf (dot_file, "    node%d -> node%d [style = invis, weight = 100];", i, i + 1);
    }

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] == POISON && i != 0)
            fprintf(dot_file, "    node%d:f0 -> node%d:f0 [color=purple];\n", i, list->next[i]);
        else
            fprintf(dot_file, "    node%d:f0 -> node%d:f0 [color=blue];\n", i, list->next[i]);
    }

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->prev[i] != -1)
            fprintf(dot_file, "    node%d:f3 -> node%d:f3 [color=green, dir=back];\n", list->prev[i], i);
    }
    
    fprintf(dot_file, "}\n");

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