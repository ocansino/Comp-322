#include <stdio.h>
#include <stdlib.h>
/*
Comp 322 Robert McIlhenny
Oscar Cansino
Assignment #1 Process Creation Hierarchy
*/

/* Define structures and global variables, including
linked list type and PCB type */
void exit_program();
int max_processes;

struct node1 {
   int process;
   struct node1 *link;
};
typedef struct node1 linked_list_type;

struct node2 {
   int parent;
   linked_list_type *children;
} *pcb = NULL;
typedef struct node2 pcb_type;



/***************************************************************/
void enterParams() {
	/* declare local vars */
   int choice = 0;
   int i;
	/* prompt for maximum number of processes */
   printf("Enter maximum number of processes: ");
   scanf("%d", &choice);
   max_processes = choice;
   printf("%d\n\n", max_processes);
   
	/* allocate memory for dynamic array of PCBs */
   pcb = (pcb_type *)malloc(sizeof(pcb_type) *max_processes);
	/* Define PCB[0] */
   pcb[0].parent = 0;
   pcb[0].children= NULL;
	/* Intitialize all other indices' parent to -1 */
   for(i = 1; i <= max_processes - 1; i++){
      pcb[i].parent = -1;
   }
   
   return;
}
	
/***************************************************************/
void createChild() {
	/* define local vars */
   int choice = 0;
   int q = 1;
   int p = 0;
   linked_list_type *new_child, *next_child;
   int num_children;
	/* prompt for parent process index */
   printf("Enter the parent process index: ");
   scanf("%d", &choice);
   printf("%d\n", choice);
	p = choice;
   /* search for next unused process q (parent=-1), using while loop */ 
   while(pcb[q].parent != -1){
      q++;
   }
	/* allocate memory for new child PCB[q], set process index and initilize link to NULL */ 
   new_child = (linked_list_type*)malloc(sizeof(linked_list_type));
   new_child->process=q;
   new_child->link = NULL;
	/* record the parent's index p in PCB[q] */
   pcb[q].parent = p; 
	
   /* initialize the list of children of PCB[q] as empty (NULL) */
   pcb[q].children = NULL;
	/* create a new link containing the child's index q and 
	appends the link to the end of the linked list of PCB[p] */
   if(pcb[p].children == NULL){
      pcb[p].children = new_child; 
      num_children = 1;
      
   }
   else{
      
      next_child = pcb[p].children;
      num_children = 2;
      
      while(next_child->link != NULL){
         
         next_child = next_child -> link; 
         num_children++;
      }
   
      next_child->link = new_child;
   }
	/* print message: cr[p]	creates nth child of PCB[p] at PCB[q] */
	if(num_children == 1){
      printf("cr[%d]\t /*creates %dst child of PCB[%d] at PCB[%d]*/ \n\n", p, num_children, p, q);
   }
   else if(num_children == 2){
      printf("cr[%d]\t /*creates %dnd child of PCB[%d] at PCB[%d]*/ \n\n", p, num_children, p, q);
   }
   else if(num_children == 3){
      printf("cr[%d]\t /*creates %drd child of PCB[%d] at PCB[%d]*/ \n\n", p, num_children, p, q);
   }
   else{
      printf("cr[%d]\t /*creates %dth child of PCB[%d] at PCB[%d]*/ \n\n", p, num_children, p, q);
   }
   return;
}

/***************************************************************/
void destroyRecursion(linked_list_type *node) {
	//takes as parameter a variable of linked list type
   /* declare local vars */
   int q;
	/* if node parameter passed is NULL, return */
   if(node == NULL){
      return;
   }
	/* else recursively call this procedure on node's link field */
   else{
      
	/* set q to node's process field */
      destroyRecursion(node->link);
      q = node->process;
	/* recursively call this procedure on pcb[q]'s children field */
      destroyRecursion(pcb[q].children);
	/* print message of PCB[q] deleted */
      printf("PCB[%d] ", q);
	/* free memory allocated by the node parameter */
      free(node);
	/* set pcb[q]'s parent to -1 */
      pcb[q].parent = -1;
	/* set node paramter to NULL */
      node = NULL;
	}
   return;
}

/***************************************************************/
void destroy() {
	/* delcare local vars */
	int p;
	/* prompt for parent process p */
   printf("Enter the process whose descendants are to be destroyed: ");
   scanf("%d", &p);
   printf("%d\n", p);
	/* print message of descendants to be destroyed */
   printf("de[%d]\t/* destroys all descendants of PCB[%d] which includes: \n", p, p);
   /* call OPTION 3 recursive procedure on pcb[p]'s children */
   destroyRecursion(pcb[p].children);
	/* set pcb[p]'s children to NULL */
   pcb[p].children = NULL;
   printf(" */\n\n");
	return;
}

/***************************************************************/
void freeMem() {
	/* if pcb is not NULL */
		/* if pcb[0]'s children is not NULL */
			/* call OPTION #3 recursive procedure on pcb[0]' children */
		/* free memory allocated for pcb */
      free(pcb);
	return;
}

void printMenu(){
	int choice;
	do{
		choice = 0;
      printf("Process creation and destruction\n");
      printf("--------------------------------\n");
      printf("1) Enter parameters\n");
      printf("2) Create a new child process\n");
      printf("3) Destroy all descendants of a process\n");
      printf("4) Quit program and free memory\n");
      printf("\nEnter selection: ");
		scanf("%d", &choice);
      printf("%d\n", choice);
		switch(choice){
			case 1:
				enterParams();
				break;
			case 2:
				createChild();
				break;
			case 3:
            destroy();
				break;
         case 4:
            exit_program();
				break;
			default:
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;	
		}
	}while(choice != 4);
}


/***************************************************************/
int main() {
	/*declare local vars */
	/* until user quits, print menu, prompt for user's choice, call appropriate procedure */
   printMenu();
   
	return 1;
}

void exit_program(){
   freeMem();
   printf("Quitting program\n");
   exit(0);
}

