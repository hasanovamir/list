#include "list.h"

int main (void)
{
    list_t list = {};

    if (ListInit (&list, 20))
        return EXIT_FAILURE;
    if (ListInsert (&list, 0, 10))
        return EXIT_FAILURE;
    if (ListInsert (&list, 1, 20))
        return EXIT_FAILURE;
    if (ListInsert (&list, 2, 30))
        return EXIT_FAILURE;
    if (ListInsert (&list, 3, 40))
        return EXIT_FAILURE;
    if (ListInsert (&list, 4, 50))
        return EXIT_FAILURE;
    if (ListInsert (&list, 2, 25))
        return EXIT_FAILURE;

    ListDump (&list, "end");

    ListDestroy (&list);

    return EXIT_SUCCESS;
}