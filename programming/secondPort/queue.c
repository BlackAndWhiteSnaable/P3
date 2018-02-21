#include "defs.h"

// Add element to queue
void push_queue(char coords)
{
    //abort if maximum number of nodes is exceeded
    if (queue_count<numnodes){
        int i;
        //check if the node is already in the queue, return FAIL
        for(i=0;i<queue_count;i++) if(queue[i]==coords) break;
        queue[queue_count]=coords; queue_count++;
        //return SUCCES
        P1OUT ^= 0x01;
    }
}

// remove one element from head of queue
//TODO returns NULL a bit too often
char pop_queue()
{
    //check for popping more elements than in queue
    if (queue_count<=0) return 0;
    char res=queue[0];
    int i;
    for (i=0;i<queue_count;i++) queue[i]=queue[i+1];
    queue[queue_count]=(char)0;
    queue_count--;
    return res;
}

/*--PUSHES COORDINATES TO THE STACK--
 * will later be used to calculate the actual path and the movement stack
 */
void push_stack(char coords)
{
    //abort if maximum number of nodes is exceeded
    if (stack_count<numnodes){
        int i;
        //check if the node is already in the stack, return FAIL
        for(i=0;i<stack_count;i++) if(stack[i]==coords) break;
        stack[stack_count]=coords; stack_count++;
        //return SUCCES
        P1OUT ^= 0x01;
    }
}

char pop_stack()
{
    //check for popping more elements than in queue
    if (stack_count<=0) return 0;
    char res=stack[stack_count];
    int i;
    for (i=stack_count;i>=0;i--) stack[i]=stack[i+1];
    stack[stack_count]=(char)0;
    stack_count--;
    return res;
}

void push_move_stack(char move)
{
    //abort if maximum number of nodes is exceeded
    if (move_stack_count<numnodes){
        int i;
        //check if the node is already in the move_stack, return FAIL
        for(i=0;i<move_stack_count;i++) if(move_stack[i]==move) break;
        move_stack[move_stack_count]=move; move_stack_count++;
        //return SUCCES
        P1OUT ^= 0x01;
    }
}
