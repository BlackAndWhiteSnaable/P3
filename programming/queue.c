#include "defs.h"

// Add element to stack
void push(Queue **HoQ, Nodes *new_node)
{

  printf("Inside function: HoQ = %p\n", HoQ);
  printf("Inside function: *HoQ = %p\n", *HoQ);
  printf("Inside function: &HoQ = %p\n", &HoQ);

    if(!*HoQ) {
        printf("Inside function: HoQ is NULL\n");
    } else {
        printf("Inside function: HoQ is NOT NULL\n");
    }

    Queue *tmp;
    tmp = (Queue *)malloc(sizeof(Queue)); // Allocate new queue element struct in memory

    tmp->node = new_node;
    tmp->next = NULL;

    printf("Inside function: tmp = %p\n", tmp);

    // Stack is empty, insert new Queue element as head
    if (!*HoQ) {
        *HoQ = tmp; // Point HoQ to the new queue element

    // First element in queue has higher movecost than the new element
    // So insert new element as first element, and update next pointer
    } else if((*HoQ)->node->movecost > new_node->movecost) {
		tmp->next = *HoQ;
		*HoQ = tmp;

    // Insert new element before existing element with higher movecost value
    } else {
        Queue *cur;
        cur = *HoQ;
        while(cur->next != NULL && cur->next->node->movecost <= new_node->movecost) {
			cur = cur->next; // Next node
		}
        tmp->next = cur->next;                            // in new stack element set next pointer to current start stack element
        cur->next = tmp;                                  // set start stack element to point to the new stack element
    }
}

// remove one element from start of queue
Nodes *pop(Queue **HoQ)
{
    if (!*HoQ) {
        printf("Nothing to pop, queue is empty\n");

        return NULL;
    } else {
        Nodes *node;
        node = (*HoQ)->node;

        Queue *tmp;                                     // tmp pointer to struct
        tmp = (*HoQ)->next;                            // set pointer to 2nd stack element from start
        free(*HoQ);                                  // free allocated memory for 1st stack element
        *HoQ = tmp;                                  // set 2nd stack element to 1st stack element

        return node;
    }
}

// print number of elements in stack and their values
void printQueue(Queue *HoQ) {
    if(HoQ == NULL)
    {
        printf("Print what? Queue is empty\n");
    }
    else
    {
        Queue *cur; // pointer to node currently being traversed
        int i=1; // count stack element position

        for (cur = HoQ; cur != NULL; cur = cur->next)
        {
            printf("%d. Queue element is node[%d][%d] with movecost: %d\n", i, cur->node->position.x, cur->node->position.y, cur->node->movecost);
            i++;
        }
    }
}

