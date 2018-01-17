#include "defs.h"

void move_next(Robot *robot){
  // Simulate move south east until finish is reached
  robot->pos.x++;
  robot->pos.y++;
}

/// Add element to movement stack
void push_move_stack(MoveStack **head, unsigned char new_move)
{
  //printf("[DEV]\tpushing 0x%02x to movement stack\n\n",new_move);
  MoveStack *tmp;               // pointer to a struct of type MoveStack
  //                        // tmp points to struct allocated in memory
  tmp = (MoveStack *)malloc(sizeof(MoveStack));
  tmp->next = NULL;

  if (!*head)               // add element to empty stack
  {
    *head = tmp;            // set pointer to first element = new stack element tmp
    //(*head)->next = NULL;   // first element has no next so set to NULL
  }
  else                      // add element to top of existing stack element(s)
  {
    tmp->next = *head;      // in new stack element set next pointer to current top stack element
    *head = tmp;            // set top stack element to point to the new stack element
  }
  (*head)->movement = new_move; // set value of the new stack element to val passed to function
}


///pops from movement stack
unsigned char pop_move(MoveStack **head)
{
    if (!*head) {
        return 0;
    } else {
        unsigned char move;
        move = (*head)->movement;

        MoveStack *tmp;                                     // tmp pointer to struct
        tmp = (*head)->next;                            // set pointer to 2nd queue element from head
        free(*head);                                  // free allocated memory for 1st queue element
        *head = tmp;                                  // set 2nd queue element to 1st queue element

        return move;
    }
}
