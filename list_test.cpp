#include "list.h"

//--------------------------------------------------------------------------------

TEST(List, Init)
{
    list_t list = {};

    ListInit (&list, 20);

    EXPECT_NE (list.data, nullptr);
    EXPECT_NE (list.next, nullptr);
    EXPECT_NE (list.prev, nullptr);
    EXPECT_EQ (list.capacity,  20);
    EXPECT_EQ (list.free,       1);

    for (int i = 1; i < list.capacity - 1; i++) {
        EXPECT_EQ (list.data[i], POISON);
        EXPECT_EQ (list.next[i], i + 1);
        EXPECT_EQ (list.prev[i], -1);
    }

    EXPECT_EQ (list.data[0],  POISON);
    EXPECT_EQ (list.data[19], POISON);
    EXPECT_EQ (list.next[0],   0);
    EXPECT_EQ (list.next[19],  0);
    EXPECT_EQ (list.prev[19], -1);
    EXPECT_EQ (list.prev[0],  0);
}

//--------------------------------------------------------------------------------

TEST(LIST, InsertAfter)
{
    list_t list = {};

    ListInit (&list, 20);

    ListInsertAfter (&list, 0, 10);
    ListInsertAfter (&list, 1, 20);
    ListInsertAfter (&list, 2, 30);
    ListInsertAfter (&list, 3, 40);
    ListInsertAfter (&list, 1, 15);

    EXPECT_EQ (list.size, 5);
    EXPECT_EQ (list.free, 6);
    EXPECT_EQ (list.head, 1);
    EXPECT_EQ (list.tail, 4);

    EXPECT_EQ (list.data[1], 10);
    EXPECT_EQ (list.data[2], 20);
    EXPECT_EQ (list.data[3], 30);
    EXPECT_EQ (list.data[4], 40);
    EXPECT_EQ (list.data[5], 15);

    EXPECT_EQ (list.next[1], 5);
    EXPECT_EQ (list.next[2], 3);
    EXPECT_EQ (list.next[3], 4);
    EXPECT_EQ (list.next[4], 0);
    EXPECT_EQ (list.next[5], 2);

    EXPECT_EQ (list.prev[1], 0);
    EXPECT_EQ (list.prev[2], 5);
    EXPECT_EQ (list.prev[3], 2);
    EXPECT_EQ (list.prev[4], 3);
    EXPECT_EQ (list.prev[5], 1);
    EXPECT_EQ (list.prev[0], 4);
}

//--------------------------------------------------------------------------------

TEST(LIST, InsertToStart)
{
    list_t list = {};

    ListInit (&list, 20);

    ListInsertToStart (&list, 10);
    ListInsertToStart (&list, 20);
    ListInsertToStart (&list, 30);
    ListInsertToStart (&list, 40);
    ListInsertToStart (&list, 15);

    EXPECT_EQ (list.size, 5);
    EXPECT_EQ (list.free, 6);
    EXPECT_EQ (list.head, 5);
    EXPECT_EQ (list.tail, 1);

    EXPECT_EQ (list.data[1], 10);
    EXPECT_EQ (list.data[2], 20);
    EXPECT_EQ (list.data[3], 30);
    EXPECT_EQ (list.data[4], 40);
    EXPECT_EQ (list.data[5], 15);

    EXPECT_EQ (list.next[0], 5);
    EXPECT_EQ (list.next[5], 4);
    EXPECT_EQ (list.next[4], 3);
    EXPECT_EQ (list.next[3], 2);
    EXPECT_EQ (list.next[2], 1);
    EXPECT_EQ (list.next[1], 0);

    EXPECT_EQ (list.prev[5], 0);
    EXPECT_EQ (list.prev[4], 5);
    EXPECT_EQ (list.prev[3], 4);
    EXPECT_EQ (list.prev[2], 3);
    EXPECT_EQ (list.prev[1], 2);
    EXPECT_EQ (list.prev[0], 1);
}

//--------------------------------------------------------------------------------

TEST(LIST, Delete)
{
    list_t list = {};

    ListInit (&list, 20);

    ListInsertAfter (&list, 0, 10);
    ListInsertAfter (&list, 1, 20);
    ListInsertAfter (&list, 2, 30);
    ListInsertAfter (&list, 3, 40);
    ListInsertAfter (&list, 1, 15);
    ListDelete      (&list, 3);

    EXPECT_EQ (list.size, 4);
    EXPECT_EQ (list.free, 3);
    EXPECT_EQ (list.head, 1);
    EXPECT_EQ (list.tail, 4);

    EXPECT_EQ (list.data[1], 10);
    EXPECT_EQ (list.data[2], 20);
    EXPECT_EQ (list.data[4], 40);
    EXPECT_EQ (list.data[5], 15);
    EXPECT_EQ (list.data[3], POISON);

    EXPECT_EQ (list.next[1], 5);
    EXPECT_EQ (list.next[2], 4);
    EXPECT_EQ (list.next[3], 6);
    EXPECT_EQ (list.next[4], 0);
    EXPECT_EQ (list.next[5], 2);

    EXPECT_EQ (list.prev[1],  0);
    EXPECT_EQ (list.prev[2],  5);
    EXPECT_EQ (list.prev[3], -1);
    EXPECT_EQ (list.prev[4],  2);
    EXPECT_EQ (list.prev[5],  1);
    EXPECT_EQ (list.prev[0],  4);
}

//--------------------------------------------------------------------------------