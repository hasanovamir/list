#include "list.h"

//--------------------------------------------------------------------------------

int main (void)
{
    list_t list = {};

    ListInit (&list, 4);

    ListInsertAfter (&list, 0, 10);
    ListDump (&list, "first");
    ListTerminalDump (&list);
    ListInsertAfter (&list, 0, 20);
    ListDump (&list, "second");
    ListInsertAfter (&list, 0, 30);
    ListDump (&list, "third");
    ListDelete (&list, 2);
    ListInsertAfter (&list, 1, 74);
    ListInsertAfter (&list, 3, 92);
    ListDump (&list, "fourth");

    ListTerminalDump (&list);

    ListDestroy (&list);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------