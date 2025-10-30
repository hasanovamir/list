#include "list.h"

//--------------------------------------------------------------------------------

list_err_t ListInsert  (list_t* list, int idx, int val)
{
    DEBUG_ASSERT (list != NULL);

    if (idx < 0 || idx > list->capacity) //in arr
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }

    if (list->data[idx] == POISON && idx != 0) // not empty cell
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }
    
    int free = list->free;

    if (ChangeFree (list))
        return LIST_GET_NEXT_FREE_ERR;

    list->data[free] = val;

    if (idx == 0 && free == 1) // insert to start of empty arr
    {
        list->head = free;
        list->prev[free] = 0;
        list->next[free] = 0;
    }
    else if (idx == 0) //insert to start of not empty arr// new head
    {
        list->prev[free] = 0;
        list->next[free] = list->head;
        list->head = free;
    }
    else if (list->data[list->next[idx]] != POISON) // insert to middle of arr
    {
        int next_el = list->next[idx];

        list->next[idx]  = free;
        list->next[free] = next_el;
        list->prev[free]    = idx;
        list->prev[next_el] = free;
    }
    else //new tail // insert to end of arr
    {
        list->next[list->tail]  = free;
        list->next[free] = 1;
        list->prev[free] = list->tail;
        list->tail = free;
    }

    list->size++;

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ChangeFree (list_t* list)
{
    DEBUG_ASSERT (list != NULL);

    list->free = list->next[list->free];

    if (list->free == 0)
    {
        if (UpSizeList (list))
            return LIST_UP_SIZE_ERR;
    }

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------