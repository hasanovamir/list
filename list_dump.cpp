#include "list.h"

//--------------------------------------------------------------------------------

list_err_t FillDotFile (list_t* list, const char* file_name)
{
    DEBUG_ASSERT (file_name != NULL);

    FILE* dot_file = fopen (file_name, "w");
    
    if (dot_file == NULL)
    {
        PRINTERR (LIST_OPEN_FILE_ERR);
        return   (LIST_OPEN_FILE_ERR);
    }

    MakeDumpTitle (dot_file);

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->data[i] == POISON)
        {
            MakeDumpNode (dot_file, i, i, list->data[i], list->prev[i], list->next[i], "yellow");
        }
        else
        {
            MakeDumpNode (dot_file, i, i, list->data[i], list->prev[i], list->next[i], "lime");
        }
    }

    for (int i = 0; i < list->capacity; i++)
    {
        if (i < list->capacity - 1) // i + 1 < cap // invis node connection
        {
            MakeDumpEdge (dot_file, i, i + 1, "invis");
        }

        if (list->data[i] == POISON && i != 0) // free connection
        {
            MakeDumpEdge (dot_file, i, list->next[i], "purple");
        }
        else // connection of ordinary members
        {
            MakeDumpEdge (dot_file, i, list->next[i], "blue" );
            MakeDumpEdge (dot_file, i, list->prev[i], "green");
        }
    }
    
    fprintf(dot_file, "}\n");

    fclose(dot_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

void MakeDumpTitle (FILE* dot_file)
{
    DEBUG_ASSERT (dot_file != NULL);

    fprintf(dot_file, "digraph ListDump {\n\trankdir=LR;\n\tnode [shape=Mrecord, fontname=\"Courier\"];\n\n\n\tgraph [splines=ortho]\n\toverlap=false;\n\n");
}

//--------------------------------------------------------------------------------

void MakeDumpNode (FILE* dot_file, int node_number, int idx, list_data_t data, int prev, int next, const char* color)
{
    DEBUG_ASSERT (dot_file != NULL);
    DEBUG_ASSERT (color    != NULL);

    if (data == POISON)
        fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:PSN | <prev> prev:%d | <next> next:%d\", style=filled, color=%s];\n", 
            node_number, idx, prev, next, color);
    else
            fprintf(dot_file, "\tnode%d [label=\"<idx> idx:%d | <data> data:%d | <prev> prev:%d | <next> next:%d\", style=filled, color=%s];\n", 
            node_number, idx, data, prev, next, color);
}

//--------------------------------------------------------------------------------

void MakeDumpEdge (FILE* dot_file, int node_num_1, int node_num_2, const char* color)
{
    DEBUG_ASSERT (dot_file != NULL);
    DEBUG_ASSERT (color    != NULL);

    if (strcmp (color, "invis") == 0)
        fprintf (dot_file, "\tnode%d -> node%d [style = invis, weight = 100];\n", node_num_1, node_num_2);
    else
        fprintf(dot_file, "\tnode%d -> node%d [color=%s, constraint=false];\n", node_num_1, node_num_2, color);
}

//--------------------------------------------------------------------------------

list_err_t ListDump (list_t* list)
{
    list->num_calls++;

    char dot_file_name[20];
    char png_file_name[20];
    char command[50];
    
    snprintf(dot_file_name, sizeof(dot_file_name), "dot/%s_%d.dot", "call", list->num_calls);
    snprintf(png_file_name, sizeof(png_file_name), "png/%s_%d.svg", "call", list->num_calls);
    
    if (FillDotFile (list, dot_file_name))
    {
        return LIST_OPEN_FILE_ERR;
    }

    printf("Generated DOT file:  %s\n", dot_file_name);
    
    snprintf(command, sizeof(command), "dot -Tsvg %s -o %s", dot_file_name, png_file_name);

    int result = system(command);
    
    if (result == 0)
    {
        printf("Generated PNG image: %s\n", png_file_name);
    }
    else
    {
        PRINTERR (LIST_SYS_FUNC_ERR);
        return   (LIST_SYS_FUNC_ERR);
    }

    if (ListFillHtml (list, png_file_name))
        return LIST_OPEN_FILE_ERR;

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListStartFillHtml (void)
{
    FILE* html_file = fopen ("list_dump.html", "w");

    if (html_file == NULL)
    {
        PRINTERR (LIST_OPEN_FILE_ERR);
        return   (LIST_OPEN_FILE_ERR);
    }

    fprintf (html_file, "<!DOCTYPE html>\n<html>\n<head>\n\t<title>LIST DUMP</title>\n</head>\n<body>\n");

    fclose (html_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListFillHtml (list_t* list, const char* file_name)
{
    FILE* html_file = fopen ("list_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (LIST_OPEN_FILE_ERR);
        return   (LIST_OPEN_FILE_ERR);
    }

    char string[500] = "";

    snprintf (string, 500, "\t<h2>CALL = #%d</h2>\n\t<p>HEAD = %d</p>\n\t<p>TAIL = %d</p>\n\t<p>FREE = %d</p>\n\t<p>CAPACITY = %d</p>\n\t<img src=\"%s\">\n\n", 
        list->num_calls, list->head, list->tail, list->free, list->capacity, file_name);

    fprintf (html_file, string);

    fclose (html_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListEndFillHtml (void)
{
    FILE* html_file = fopen ("list_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (LIST_OPEN_FILE_ERR);
        return   (LIST_OPEN_FILE_ERR);
    }

    fprintf (html_file, "</body>\n</html>");

    fclose (html_file);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListTerminalDump (list_t* list)
{
    LIST_VERIFY (list);

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

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

void PrintNode ( ... )
{

}