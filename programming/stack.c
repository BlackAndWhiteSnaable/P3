#include "defs.h"

// Add element to stack
void push_stack(Stack **head, Nodes *new_node)
{
    Stack *tmp;                                         // pointer to a struct of type Stack
    tmp = (Stack *)malloc(sizeof(Stack));                 // tmp points to struct allocated in memory

    if (!*head) {                                     // add element to empty stack
        *head = tmp;                                    // set pointer to first element = new stack element tmp
        (*head)->next = NULL;                             // first element has no next so set to NULL
    } else {                                            // add element to top of existing stack element(s)
        tmp->next = *head;                              // in new stack element set next pointer to current top stack element
        *head = tmp;                                    // set top stack element to point to the new stack element
    }
    (*head)->node = new_node;                                   // set value of the new stack element to val passed to function
}

// print number of elements in stack and their values
void print_stack(Stack *head) {
    if(!head)
    {
        printf("Print what? Stack is empty\n");
    } else {
        Stack *cur; // pointer to node currently being traversed
        int i=1; // count stack element position

        for (cur = head; cur != NULL; cur = cur->next)
        {
            printf("%d. Stack element is node[%d][%d] with movecost: %d\n", i, cur->node->position.x, cur->node->position.y, cur->node->movecost);
            i++;
        }
    }
}
