#include "list.h"

//--------------------------------------------------------------------------------

list_err_t ListCheck (list_t* list)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);
    
    if (list->capacity < 0)
    {
        PRINTERR (LIST_INVALID_CAPACITY_SIZE);
        return   (LIST_INVALID_CAPACITY_SIZE);
    }
    if (list->free >= list->capacity || list->free < 0)
    {
        PRINTERR (LIST_INVALID_FREE_VAL);
        return   (LIST_INVALID_FREE_VAL);
    }
    if (list->head >= list->capacity || list->head < 0)
    {
        PRINTERR (LIST_INVALID_HEAD);
        return   (LIST_INVALID_HEAD);
    }
    if (list->tail >= list->capacity || list->tail < 0)
    {
        PRINTERR (LIST_INVALID_TAIL);
        return   (LIST_INVALID_TAIL);
    }
    if (list->size >= list->capacity || list->size < 0)
    {
        PRINTERR (LIST_INVALID_SIZE);
        return   (LIST_INVALID_SIZE);
    }

    for (int i = 0; i < list->size; i++)
    {
        if (i != list->prev[list->next[i]])
        {   
            PRINTERR (LIST_INCORRECT_NUMBERING)
            return   (LIST_INCORRECT_NUMBERING);
        }
    }

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------