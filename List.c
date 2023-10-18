#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj
{
    int data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Helper Function Declaration ------------------------------------------------
bool isEmpty(List L);

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data)
{
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList()
{
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (!isEmpty(*pL))
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// Returns front element of L.
// Pre: length()>0
int front(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// Returns back element of L.
// Pre: length()>0
int back(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "List Error: calling get() on List index < 0\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true if Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B)
{
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;

    while (eq && N != NULL)
    {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    while (!isEmpty(L))
    {
        deleteFront(L);
    }

    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "List Error: calling set() on List index < 0\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(L))
    {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(L))
    {
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int idx = index(L);
    if (idx > 0)
    {
        L->cursor = L->cursor->prev;
        L->index -= 1;
    }
    else if (idx == 0)
    {
        L->cursor = NULL;
        L->index = -1;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int idx = index(L);
    int len = length(L);
    if (idx >= 0 && idx < len - 1)
    {
        L->cursor = L->cursor->next;
        L->index += 1;
    }
    else if (idx == len - 1)
    {
        L->cursor = NULL;
        L->index = -1;
    }
}

// Insert new element into L.
// If L is non-empty, insertion takes place before front element.
void prepend(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        L->front = L->back = newNode(x);
    }
    else
    {
        Node oldFront = L->front;

        Node N = newNode(x);
        N->next = oldFront;

        L->front = N;
        oldFront->prev = N;
        L->index += 1;
    }

    L->length += 1;
}

// Insert new element into L.
// If L is non-empty, insertion takes place after back element.
void append(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        L->front = L->back = newNode(x);
    }
    else
    {
        Node oldBack = L->back;

        Node N = newNode(x);
        N->prev = oldBack;

        L->back = N;
        oldBack->next = N;
    }

    L->length += 1;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "List Error: calling insertBefore() on List index < 0\n");
        exit(EXIT_FAILURE);
    }
    Node cursorPrev = L->cursor->prev;

    if (cursorPrev == NULL)
    {
        prepend(L, x);
    }
    else
    {
        Node N = newNode(x);
        N->next = L->cursor;
        N->prev = cursorPrev;
        cursorPrev->next = N;
        L->cursor->prev = N;

        L->index += 1;
        L->length += 1;
    }
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "List Error: calling insertAfter() on List index < 0\n");
        exit(EXIT_FAILURE);
    }
    Node cursorNext = L->cursor->next;

    if (cursorNext == NULL)
    {
        append(L, x);
    }
    else
    {
        Node N = newNode(x);
        N->prev = L->cursor;
        N->next = cursorNext;

        L->cursor->next = N;
        cursorNext->prev = N;

        L->length += 1;
    }
}

// Delete the front element.
// Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node oldFront = L->front;
    L->front = L->front->next;
    if (L->front != NULL)
    {
        L->front->prev = NULL;
    }

    L->length -= 1;
    L->index -= 1;
    if (index(L) == -1)
    {
        L->cursor = NULL;
    }
    freeNode(&oldFront);
}

// Delete the back element.
// Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node oldBack = L->back;
    L->back = L->back->prev;
    if (L->back != NULL)
    {
        L->back->next = NULL;
    }
    L->length -= 1;
    if (index(L) >= length(L))
    {
        L->index = -1;
        L->cursor = NULL;
    }
    freeNode(&oldBack);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        fprintf(stderr, "List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "List Error: calling delete() on List index < 0\n");
        exit(EXIT_FAILURE);
    }
    Node cursor = L->cursor;
    if (cursor->prev == NULL && cursor->next != NULL)
    {
        deleteFront(L);
    }
    else if (cursor->prev != NULL && cursor->next == NULL)
    {
        deleteBack(L);
    }
    else
    {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        L->index = -1;
        L->length -= 1;
        freeNode(&cursor);
    }
    L->cursor = NULL;
}

// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L)
{
    Node N = NULL;

    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    for (N = L->front; N != NULL; N = N->next)
    {
        fprintf(out, "%d ", N->data);
    }
}

// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L)
{
    Node N = NULL;

    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List duplicate = newList();
    for (N = L->front; N != NULL; N = N->next)
    {
        append(duplicate, N->data);
    }
    freeNode(&N);
    N = NULL;

    return duplicate;
}

// Helper Functions -----------------------------------------------------------

// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return (L->length == 0);
}
