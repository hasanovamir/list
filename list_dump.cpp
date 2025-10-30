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
    fprintf(dot_file, "    rankdir=LR;\n"     );
    fprintf(dot_file, "    node [shape=record, fontname=\"Courier\"];\n\n");
    
    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] != POISON)
        {
            fprintf(dot_file, "    node%d [label=\"<f0> idx:%d | <f1> data:%d | <f2> prev:%d | <f3> next:%d\"];\n", 
                    i, i, list->data[i], list->prev[i], list->next[i]);
        }
    }
    
    fprintf(dot_file, "\n");
    
    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] != POISON)
        {
            fprintf(dot_file, "    node%d:f3 -> node%d:f1 [color=blue];\n", i, list->next[i]);
        }
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
    
    FillDotFile(list, dot_file_name);

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
        printf("Error: Graphviz not installed? Run: sudo apt-get install graphviz\n");
        return LIST_SYS_FUNC_ERR;
    }
}

//--------------------------------------------------------------------------------