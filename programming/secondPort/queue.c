#include "defs.h"

// Add element to queue
int push_queue(char coords)
{
    //abort if maximum number of nodes is exceeded
    if (queue_count>=numnodes) return 0;
    int i;
    //check if the node is already in the queue, return FAIL
    for(i=0;i<queue_count;i++) if(queue[i]==coords) return 0;
    queue[queue_count]=coords; queue_count++;
    //return SUCCES
    P1OUT ^= 0x01;
    return 1;

}


// remove one element from head of queue
//TODO returns NULL a bit too often
char pop_queue()
{
    //check for popping more elements than in queue
    if (queue_count<=0) return 0;
    char res=queue[0];
    int i;
    for (i=0;i<numnodes-1;i++) queue[i]=queue[i+1];
    queue[8]=(char)0;
    queue_count--;
    return res;
}
