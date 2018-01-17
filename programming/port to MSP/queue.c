#include "defs.h"

// Add element to queue
void push_queue(volatile Queue **head, volatile Nodes *new_node)
{
  volatile Queue *tmp;
  tmp = (Queue *)malloc(sizeof(Queue)); // Allocate new queue element struct in memory

  // queue is empty, insert new Queue element as head
  if (!*head) {
    *head = tmp; // Point head to the new queue element
    (*head)->next = NULL;

  // First element in queue has higher movecost than the new element
  // So insert new element as first element, and update next pointer
  } else if((*head)->node->movecost > new_node->movecost) {
  tmp->next = *head;
  *head = tmp;

  // Insert new element before existing element with higher movecost value
  } else {
    volatile Queue *cur;
    cur = *head;
    while(cur->next != NULL && cur->next->node->movecost <= new_node->movecost) {
    cur = cur->next; // Next node
  }
    tmp->next = cur->next;                            // in new queue element set next pointer to current head queue element
    cur->next = tmp;                                  // set head queue element to point to the new queue element
  }
  // Store pointer to node in the new queue element
  tmp->node = new_node;
}


// remove one element from head of queue
volatile Nodes *pop(volatile Queue **head)
{
    if (!*head) {
        return NULL;
    } else {
        volatile Nodes *node;
        node = (*head)->node;

        volatile Queue *tmp;                                     // tmp pointer to struct
        tmp = (*head)->next;                            // set pointer to 2nd queue element from head
        free(*head);                                  // free allocated memory for 1st queue element
        *head = tmp;                                  // set 2nd queue element to 1st queue element

        return node;
    }
}
