#include "list.h"

//--------------------------------------------------------------------------------

int main (void)
{
    list_t list = {};

    ListInit (&list, 4);

    ListInsertAfter (&list, 0, 10);
    ListTerminalDump (&list);
    ListInsertAfter (&list, 0, 20);
    ListTerminalDump (&list);
    ListInsertAfter (&list, 0, 30);
    ListTerminalDump (&list);
    ListDelete (&list, 2);
    ListTerminalDump (&list);

    ListDestroy (&list);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------