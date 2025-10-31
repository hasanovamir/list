#include "list.h"

//--------------------------------------------------------------------------------

list_err_t ListInsertAfter (list_t* list, int idx, int val)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    if (idx < 0 || idx >= list->capacity)
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }

    if (list->data[idx] == POISON && idx != 0)
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }

    int free = list->free;

    if (ChangeFree (list))
        return LIST_UP_SIZE_ERR;

    list->data[free] = val;

    int next_el = list->next[idx];

    list->next[idx]  = free;
    list->next[free] = next_el;
    list->prev[free]    = idx;
    list->prev[next_el] = free;

    list->size++;

    list->head = list->next[0];
    list->tail = list->prev[0];

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListInsertBefore (list_t* list, int idx, int val)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    if (idx < 0 || idx >= list->capacity)
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }

    if (list->data[idx] == POISON && idx != 0)
    {
        PRINTERR (LIST_INVALID_IDX);
        return LIST_INVALID_IDX;
    }

    int free = list->free;

    if (ChangeFree (list))
        return LIST_UP_SIZE_ERR;

    list->data[free] = val;

    int next_el = list->next[idx];

    list->next[free] = idx;
    list->next[list->prev[idx]] = free;
    list->prev[free] = list->prev[idx];
    list->prev[idx] = free;

    list->size++;

    list->head = list->next[0];
    list->tail = list->prev[0];

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListInsertToStart (list_t* list, int idx, int val)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    if (idx < 0 || idx >= list->capacity)
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
        return LIST_UP_SIZE_ERR;

    list->data[free] = val;

    int next_el = list->next[idx];

    list->next[0] = free;
    list->next[free] = list->head;
    list->prev[free] = 0;
    list->prev[list->head] = free;

    list->size++;

    list->head = list->next[0];
    list->tail = list->prev[0];

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ChangeFree (list_t* list)
{
    DEBUG_ASSERT (list != NULL);

    list->free = list->next[list->free];

    if (list->free == 0)
    {
        if (IncreaseList (list))
            return LIST_UP_SIZE_ERR;
    }

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t ListDelete (list_t* list, int idx)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    list->data[idx] = POISON;
    list->next[list->prev[idx]] = list->next[idx];
    list->prev[list->next[idx]] = list->prev[idx];
    list->next[idx] = list->free;
    list->prev[idx] = -1;
    list->free = idx;

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------