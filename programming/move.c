#include "defs.h"

void move_next(Robot *robot){
    // Simulate move south east until finish is reached
    robot->pos.x++;
    robot->pos.y++;
}

/// Add element to movement stack
void push_move_stack(MoveStack **head, char new_move)
{
  printf("\n[DEV]\tpushing 0x%02x to movement stack\n",new_move);
  MoveStack *tmp;               // pointer to a struct of type MoveStack
  //                        // tmp points to struct allocated in memory
  tmp = (MoveStack *)malloc(sizeof(MoveStack));

  if (!*head)               // add element to empty stack
  {
    *head = tmp;            // set pointer to first element = new stack element tmp
    (*head)->next = NULL;   // first element has no next so set to NULL
  }
  else                      // add element to top of existing stack element(s)
  {
    tmp->next = *head;      // in new stack element set next pointer to current top stack element
    *head = tmp;            // set top stack element to point to the new stack element
  }
  (*head)->movement = new_move; // set value of the new stack element to val passed to function
}

///prints the movement stack
void print_move_stack(MoveStack *head)
{
  if(!head)
  {
    printf("[WARNING]\tPrint what? Movement stack is empty\n");
  }
  else
  {
    MoveStack *cur; // pointer to node currently being traversed
    int i=1; // count stack element position

    for (cur = head; cur != NULL; cur = cur->next, i++)
    {
      printf("//------------------%2d. Stack element------------------//\n",i);
      printf("[DEV]\t0x%02x\n",cur->movement);
      //i++;
    }
  }
  printf("\n");
}
