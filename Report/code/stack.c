#include "defs.h"

// Add element to stack
void push_stack(Stack **head, Nodes *new_node)
{
  Stack *tmp;               // pointer to a Stack
  tmp = (Stack *)malloc(sizeof(Stack));

  if (!*head)               // add element to empty stack
  {
    *head = tmp;            // set pointer to first element = tmp
    (*head)->next = NULL;   // first element has no next => NULL
  }
  else                      // add element to top of existing stack
  {
    tmp->next = *head;      // in new element set *next to current top
    *head = tmp;            // set head to point to the new element
  }
  (*head)->node = new_node; // set value of new element to val passed
}

// print number of elements in stack and their values
void print_stack(Stack *head)
{
  if(!head)
  {
    printf("[WARNING]\tPrint what? Stack is empty\n");
  }
  else
  {
    Stack *cur; // pointer to node currently being traversed
    int i=1; // count stack element position

    for (cur = head; cur != NULL; cur = cur->next)
    {
      printf(
        "//-----------------%2d. Stack element-----------------//\n",
        i
      );
      printf(
        "[DEV]\tposition [%2d][%2d]",
        cur->node->position.x,
        cur->node->position.y
      );
      if (cur->node->parent) printf(
                              "\tparent [%2d][%2d]\n",
                              cur->node->parent->position.x,
                              cur->node->parent->position.y
                            );
      else printf("\n");
      i++;
    }
  }
  printf("\n");
}
