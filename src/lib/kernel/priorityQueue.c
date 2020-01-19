#include "priorityQueue.h"
#include "../debug.h"

void priorityQueue_init(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL);
    priorityQueue->head.prev = NULL;
    priorityQueue->tail.next = NULL;
    priorityQueue->head.next = &priorityQueue->tail;
    priorityQueue->tail.prev = &priorityQueue->head;
}

struct priorityQueue_elem *priorityQueue_top(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL && priorityQueue_size(priorityQueue) > 0);
    return priorityQueue->head.next;
}

struct priorityQueue_elem *priorityQueue_bottom(struct priorityQueue *priorityQueue)
{
    ASSERT(priorityQueue != NULL && priorityQueue_size(priorityQueue) > 0);
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

void priorityQueue_push(struct priorityQueue_elem *elem, struct priorityQueue *priorityQueue)
{
    ASSERT(elem != NULL);
    struct priorityQueue_elem *head = priorityQueue_head(priorityQueue);
    struct priorityQueue_elem *tail = priorityQueue_tail(priorityQueue);
    if (priorityQueue_empty(priorityQueue))
    {
        elem->next = tail;
        elem->prev = head;
        head->next = elem;
        tail->prev = elem;
    }
    else
    {
        struct priorityQueue_elem *top = priorityQueue_top(priorityQueue);
        if (top->priority < elem->priority)
        {
            elem->next = top;
            elem->prev = head;
            head->next = elem;
            top->prev = elem;
        }
        else
        {
            struct priorityQueue_elem *e = top;
            while (e != tail && e->priority > elem->priority)
            {
                e = e->next;
            }
            elem->next = e;
            elem->prev = e->prev;
            e->prev = elem;
            elem->prev->next = elem;
        }
    }
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
    return (priorityQueue_next(priorityQueue_head(priorityQueue)) == priorityQueue_tail(priorityQueue) &&
            priorityQueue_prev(priorityQueue_tail(priorityQueue)) == priorityQueue_head(priorityQueue));
}
