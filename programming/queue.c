#include "defs.h"

// initialize "index" pointer and struct called TopStack
TopStack *init_queue()
{
    TopStack *ts;                                       // new struct pointer local to the function of type TopStack
    ts = (TopStack *)malloc(sizeof(TopStack));          // set pointer equal to allocated space in memory
    ts->num = 0;                                        // set num elements to 0
    ts->start = NULL;                                   // set pointer to start of stack to NULL

    return ts; // needed, right?
}

// add element to stack
void push(TopStack *ts, Nodes *mnode)
{
    Stack *tmp;                                         // pointer to a struct
    tmp = (Stack *)malloc(sizeof(Stack));               // Allocate queue element struct in memory

    if (!ts->start) {                                   // add element to empty stack
        ts->start = tmp;                                // set pointer to first element = new stack element tmp
        ts->start->next = NULL;                         // first element has no next so set to NULL

    } else if(ts->start->node->movecost > mnode->movecost) {
		tmp->next = ts->start;
		ts->start = tmp;

    } else {
        Stack *cur;
        cur = ts->start;                                  // add element to start of existing stack element(s)
        while(cur->next != NULL && cur->next->node->movecost <= mnode->movecost) {
			cur = cur->next; // Next node
		}
        tmp->next = cur->next;                            // in new stack element set next pointer to current start stack element
        cur->next = tmp;                                  // set start stack element to point to the new stack element

    }
   // NEED to save address of node here
   // node just created should be = &mnode
    ts->num++;                                          // set number of elements to +1
}

// remove one element from start of stack
void pop(TopStack *ts)
{
    if (!ts->start) {
        printf("Nothing to pop, stack is empty\n");
    } else {
        Stack *tmp;                                     // tmp pointer to struct
        tmp = ts->start->next;                            // set pointer to 2nd stack element from start
        free(ts->start);                                  // free allocated memory for 1st stack element
        ts->start = tmp;                                  // set 2nd stack element to 1st stack element
        ts->num--;                                      // stack now has 1 less element so update num
    }
}

// empties stack using pop() to remove elements one by one
void emptyStack(TopStack *ts)
{
    while(ts->start) {                                    // ts->start always points to first stack element, pop() updates it
        pop(ts);                                        // remove element from start of stack by calling pop()
    }
}

// print number of elements in stack and their values
void printStack(TopStack *ts) {
    if(ts->num==0)
    {
        printf("Print what? Stack is empty\n");
    } else {
        printf("Queue contains %d element(s):\n", ts->num);

        Stack *cur; // pointer to node currently being traversed
        int i=1; // count stack element position

        for (cur = ts->start; cur != NULL; cur = cur->next)
        {
            printf("%d. Queue element has movecost: %d\n", i, cur->node->movecost);
            i++;
        }
    }
}
