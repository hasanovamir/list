#include "list.h"

int main (void)
{
    list_t list = {};

    if (ListInit (&list, 20))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 0, 10))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 1, 20))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 2, 30))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 3, 40))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 4, 50))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 2, 25))
        return EXIT_FAILURE;
    if (ListInsertAfter (&list, 6, 29.5))
        return EXIT_FAILURE;
    ListDelete (&list, 4);
    if (ListInsertBefore (&list, 7, 28))
        return EXIT_FAILURE;

    ListDump (&list, "end");
    ListTerminalDump (&list);

    ListDestroy (&list);

    return EXIT_SUCCESS;
}