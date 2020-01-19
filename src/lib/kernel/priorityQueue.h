#ifndef __LIB_KERNEL_PRIORITY_QUEUE_H
#define __LIB_KERNEL_PRIORITY_QUEUE_H

/* Priority queue implemented using doubly linked list.

   This implementation of a priority queue does not require
   use of dynamically allocated memory.  Instead, each structure
   that is a potential priority queue element must embed a struct priorityQueue_elem
   member.  All of the priority queue functions operate on these `struct
   priorityQueue_elem's.  The priorityQueue_entry macro allows conversion from a
   struct priorityQueue_elem back to a structure object that contains it.

   For example, suppose there is a needed for a priority queue of `struct
   foo'.  `struct foo' should contain a `struct priorityQueue_elem'
   member, like so:

      struct foo
        {
          struct priorityQueue_elem elem;
          int bar;
          ...other members...
        };

   Then a priority queue of `struct foo' can be be declared and initialized
   like so:

      struct priorityQueue foo_priorityQueue;

      priorityQueue_init (&foo_priorityQueue);

   Iteration is possible with next and prev elements and it is possible to
   convert from a struct priorityQueue_elem back to its enclosing
   structure.  Here's an example using foo_list:

      struct priorityQueue_elem *e;
      struct foo *f = priorityQueue_entry (e, struct foo, elem);
      ...do something with f...

   The interface for this priority queue is inspired by the priority_queue<> template
   in the C++ STL.  If you're familiar with priority_queue<>, you should
   find this easy to use.  However, it should be emphasized that
   these lists do *no* type checking and can't do much other
   correctness checking.  If you screw up, it will bite you.

   Glossary of priority queue terms:

     - "top": The top element in a priority queue.  Undefined in an
       empty priority queue.  Returned by priorityQueue_top().
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <list.h>

/* Priority queue element. */
struct priorityQueue_elem
{
  int priority;                    /* Priority for this element. */
  struct priorityQueue_elem *prev; /* Previous priority queue element. */
  struct priorityQueue_elem *next; /* Next priority queue element. */
};

/* Priority queue. */
struct priorityQueue
{
  struct priorityQueue_elem head; /* Priority queue head. */
  struct priorityQueue_elem tail; /* Priority queue tail. */
};

/* Converts pointer to list element LIST_ELEM into a pointer to
   the structure that LIST_ELEM is embedded inside.  Supply the
   name of the outer structure STRUCT and the member name MEMBER
   of the list element.  See the big comment at the top of the
   file for an example. */
#define priorityQueue_entry(PRIORITY_QUEUE_ELEM, STRUCT, MEMBER) ((STRUCT *)((uint8_t *)&(PRIORITY_QUEUE_ELEM)->next - offsetof(STRUCT, MEMBER.next)))

/* Priority queue initialization.

   A list may be initialized by calling priorityQueue_init():

       struct priorityQueue my_priorityQueue;
       priorityQueue_init (&my_priorityQueue);
*/
void priorityQueue_init(struct priorityQueue *);

/* Priority queue traversal. */
struct priorityQueue_elem *priorityQueue_top(struct priorityQueue *);
struct priorityQueue_elem *priorityQueue_bottom(struct priorityQueue *);

struct priorityQueue_elem *priorityQueue_head(struct priorityQueue *);
struct priorityQueue_elem *priorityQueue_tail(struct priorityQueue *);

struct priorityQueue_elem *priorityQueue_next(struct priorityQueue_elem *);
struct priorityQueue_elem *priorityQueue_prev(struct priorityQueue_elem *);

/* Priority queue insertion. */
void priorityQueue_push(struct priorityQueue_elem *);

/* Priority queue removal. */
struct priorityQueue_elem *priorityQueue_pop(struct priorityQueue *);
struct priorityQueue_elem *priorityQueue_pop_back(struct priorityQueue *);
struct priorityQueue_elem *priorityQueue_remove(struct priorityQueue_elem *);

/* Priority queue properties. */
size_t priorityQueue_size(struct priorityQueue *);
bool priorityQueue_empty(struct priorityQueue *);

#endif /* lib/kernel/priorityQueue.h */
