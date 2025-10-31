#include "list.h"

//--------------------------------------------------------------------------------

list_err_t ListInit (list_t* list, int capacity)
{
    DEBUG_ASSERT (list != NULL);

    list->free = 1;
    list->head = 0;
    list->tail = 0;
    list->capacity = capacity;

    if (capacity < 0)
    {
        PRINTERR (LIST_INVALID_CAPACITY_SIZE);
        return LIST_INVALID_CAPACITY_SIZE;
    }

    list->data = (list_data_t*) calloc (capacity, sizeof (list_data_t));

    if (list->data == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    list->next = (int*) calloc (capacity, sizeof (int));

    if (list->next == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    list->prev = (int*) calloc (capacity, sizeof (int));

    if (list->prev == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    MemSetList (list);

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

list_err_t IncreaseList (list_t* list)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    int new_capacity = list->capacity * 2;

    list->data = (list_data_t*) realloc (list->data, new_capacity);

    if (list->data == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    list->next = (int*) realloc (list->next, new_capacity);

    if (list->next == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    list->prev = (int*) realloc (list->prev, new_capacity);

    if (list->prev == NULL)
    {
        PRINTERR (LIST_ALLOCATE_ERR);
        return LIST_ALLOCATE_ERR;
    }

    return LIST_SUCCESS;
}

//--------------------------------------------------------------------------------

void ListDestroy (list_t* list)
{
    DEBUG_ASSERT (list       != NULL);
    DEBUG_ASSERT (list->data != NULL);
    DEBUG_ASSERT (list->next != NULL);
    DEBUG_ASSERT (list->prev != NULL);

    free (list->data);
    free (list->next);
    free (list->prev);

    list->data = NULL;
    list->next = NULL;
    list->prev = NULL;
}

//--------------------------------------------------------------------------------

void MemSetList (list_t* list)
{
    int* next_arr = list->next;
    
    next_arr[0] = 0;

    for (int i = 1; i < list->capacity - 1; i++)
        next_arr[i] = i + 1;

    next_arr[list->capacity - 1] = 0;

    int* prev_arr = list->prev;

    prev_arr[0] = 0;
    prev_arr[1] = 0;

    for (int i = 2; i < list->capacity; i++)
        prev_arr[i] = -1;
    for (int i = 0; i < list->capacity; i++)
        list->data[i] = POISON;
}

//--------------------------------------------------------------------------------