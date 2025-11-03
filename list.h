#ifndef LIST_H
#define LIST_H

//————————————————————————————————————————————————————————————————————————————————

#define POISON 0x66677752

//————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <stdlib.h>

//————————————————————————————————————————————————————————————————————————————————

typedef int list_data_t;

//————————————————————————————————————————————————————————————————————————————————

typedef enum
{ 
    LIST_SUCCESS,
    LIST_INVALID_IDX,
    LIST_INVALID_CAPACITY_SIZE,
    LIST_ALLOCATE_ERR,
    LIST_UP_SIZE_ERR,
    LIST_GET_NEXT_FREE_ERR,
    LIST_CHANGE_NEXT_ERR,
    LIST_CHANGE_PREV_ERR,
    LIST_OPEN_FILE_ERR,
    LIST_SYS_FUNC_ERR,
} list_err_t;

//————————————————————————————————————————————————————————————————————————————————

struct list_t
{
    list_data_t* data;
    int* next; //next_arr?
    int* prev;
    int  head;
    int  tail;
    int  free;
    int  size;
    int  capacity;
};

//————————————————————————————————————————————————————————————————————————————————

list_err_t FillDotFile       (list_t* list, const char* file_name);
list_err_t ListDump          (list_t* list, const char* file_name);
list_err_t ListInsertAfter   (list_t* list, int idx, int val);
list_err_t ListInsertBefore  (list_t* list, int idx, int val);
list_err_t ListInit          (list_t* list, int capacity);
list_err_t ListDelete        (list_t* list, int idx);
list_err_t ListInsertToStart (list_t* list, int val);
list_err_t ListInsertToEnd   (list_t* list, int val);
list_err_t ChangeFree        (list_t* list);
list_err_t IncreaseList      (list_t* list);
void       MemSetList        (list_t* list);
void       ListDestroy       (list_t* list);
void       ListTerminalDump  (list_t* list);

//————————————————————————————————————————————————————————————————————————————————

#ifndef N_DEBUG
#define DEBUG_ASSERT(cond)\
if (!cond)\
{\
    fprintf(stderr, "%s in %s:%d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define DEBUG_ASSERT(cond) ;
#endif //N_DEBUG

//————————————————————————————————————————————————————————————————————————————————

#define PRINTERR(str)\
fprintf (stderr, "%s in %s:%d in %s", #str, __FILE__, __LINE__, __PRETTY_FUNCTION__);

//————————————————————————————————————————————————————————————————————————————————

#endif //LISTH