// Priority queue used for ordering nodes by movecost
// Nodes are already declared as structs in a 2D array

// pop(list) pops first element from queue and returns the address to the node
// before removing the element from the list, not the actual node or node data.
// This way the node (address) can also be inserted in another list
//
// push(list, node, priority) (node = address to the node)

#include "defs.h"

struct node {
	int val;				// Variable to hold some value you wish to store
	int pr;					// Priority
	struct node *next;		// Pointer to next node
};

// TODO declare start node and pass address as argument, instead of using a global
// This is similar to HoL
struct node *start;

// Function declarations
void push(int val, int priority);
void pop();
void disp();

void push(int val, int priority) {
	struct node *new, *temp;
	new = (struct node *)malloc(sizeof(struct node));
	new->val = val;
	new->pr = priority;
	new->next = NULL;

	// If start node pointer is NULL queue is empty, set new node as start node
	if(start == NULL) {
		start = new;
 	// If the new node has a higher priority than the start node,
	// save the new node as starting node and point next to previous start node
    } else if(start->pr > priority) {
		new->next = start;
		start = new;
	// Save the new node in the correct list position according to its priority.
	// Traverse through the nodes in the list until a with lower priority than
	// the new node is found. Insert the new node and update its next address.
	} else {
		temp = start; // Address of the queue start node

		while(temp->next != NULL && (temp->next)->pr <= priority) {
			temp = temp->next; // Next node
		}
		new->next = temp->next; // Set new node next to point to next node in list
		temp->next = new; // Set new node to be the next node in the list (insert)
	}
disp();
}

// Remove starting node
// TODO remember to free() memory when deleting nodes
// TODO But maybe we need a move function also, if we want to move a node from one list to the other
void pop() {
	if(start != NULL) {
		struct node *temp;
		printf("\nRemoved: %d", start->val);
		start = start->next;
		free(start); // is it ok to free now?
		disp();
	} else {
		printf("\nError List Empty");
	}
}

void disp() {
	struct node *temp;
	temp = start;
	printf("\nPriority Queue: ");
	while(temp!=NULL) {
		printf("%d,%d ",temp->val, temp->pr);
		temp=temp->next;
	}
	printf("\n");
}

int main2() {
	int ch, value, pr, check=1;
	while(check==1)	{
		printf("\nIn Priority Queue Select:\n1. Insert\n2. Remove\n3. Exit\n");
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				printf("\nEnter element and its priority: ");
				scanf("%d%d",&value,&pr); //input from user
				push(value,pr);	//Send Element and its priority for insertion
				break;
			case 2:
				pop();
				break;
			case 3:
				check=0; //Stops the loop
				break;
			default:
				printf("Wrong Choice");
				printf("\nPress 1 to continue or 0 to stop");
				scanf("%d",&check);
    }
	}
	return 0;
} //end of Main


//push(robot->map.node[0][0], 123);
