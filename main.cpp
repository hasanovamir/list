#include "list.h"

//--------------------------------------------------------------------------------

// TEST_?()
// {
//     ListInsert*()
//     ListDump()
//     ListVerify*()

//     bool res = Check()

//     ASSERT(res == true)
// }

// int main()
// {
//     return ::gtest::RunAllTests();
// }

int main (void)
{
    list_t list = {};

    do
    {
        if (ListInit (&list, 4))
            break;
        if (ListInsertAfter (&list, 0, 10))
            break;
        if (ListDump (&list))
            break;
        if (ListInsertAfter (&list, 0, 20))
            break;
        if (ListDump (&list))
            break;
        if (ListInsertAfter (&list, 0, 30))
            break;
        if (ListDump (&list))
            break;
        if (ListDelete (&list, 2))
            break;
        if (ListInsertAfter (&list, 1, 74))
            break;
        if (ListInsertAfter (&list, 3, 92))
            break;
        if (ListDump (&list))
            break;
    } while (0);

    ListDump    (&list);
    ListDestroy (&list);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------