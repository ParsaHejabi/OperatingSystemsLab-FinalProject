#include "priorityQueue.h"
#include "../debug.h"

void priorityQueue_init(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    priorityQueue->head.prev = NULL;
    priorityQueue->tail.prev = NULL;
    priorityQueue->head.next = NULL;
    priorityQueue->tail.next = NULL;
}

struct priorityQueue_elem *priorityQueue_top(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    return priorityQueue->head.next;
}

struct priorityQueue_elem *priorityQueue_bottom(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    //Chra baraye list fght neveshte tail
    return priorityQueue->tail.prev;
}

struct priorityQueue_elem *priorityQueue_head(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    return &priorityQueue->head;
}

struct priorityQueue_elem *priorityQueue_tail(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    return &priorityQueue->tail;
}

struct priorityQueue_elem *priorityQueue_next(struct priorityQueue_elem *elem)
{
    // Asserts that elem is not NULL nor Tail.
    ASSERT(elem != NULL && elem->next != NULL);
    return elem->next;
}

struct priorityQueue_elem *priorityQueue_prev(struct priorityQueue_elem *elem)
{
    // Asserts that elem is not Null nor Head.
    ASSERT(elem != NULL && elem->prev != NULL);
    return elem->prev;
}

// PARSA
void priorityQueue_push(struct priorityQueue_elem *elem)
{
}

struct priorityQueue_elem *priorityQueue_pop(struct priorityQueue *priorityQueue)
{
    struct priorityQueue_elem *front = priorityQueue_top(priorityQueue);
    priorityQueue_remove(front);
    return front;
}
struct priorityQueue_elem *priorityQueue_pop_back(struct priorityQueue *priorityQueue)
{
    struct priorityQueue_elem *back = priorityQueue_bottom(priorityQueue);
    priorityQueue_remove(back);
    return back;
}
struct priorityQueue_elem *priorityQueue_remove(struct priorityQueue_elem *elem)
{
    // Asserts that elem is not NULL nor Head nor tail.
    ASSERT(elem != NULL && elem->prev != NULL && elem->next != NULL);
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    // baraye inke moshkeli k too commente list_remove gofte pish nayad
    // nmishe next o prev ro null krd?
    return elem->next;
}

size_t priorityQueue_size(struct priorityQueue *priorityQueue)
{
    struct priorityQueue_elem *e;
    size_t count = 0;
    for (e = priorityQueue_top(priorityQueue); e->next != priorityQueue_tail(priorityQueue); e = priorityQueue_next(e))
        count++;
    return count;
}

bool priorityQueue_empty(struct priorityQueue *priorityQueue)
{
    return priorityQueue_top(priorityQueue) == priorityQueue_tail(priorityQueue);
}
