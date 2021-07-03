#include <stdio.h>
#include <stdlib.h>
void exit_program();
// declare structure to store block information (id, starting address, ending address, link to next block)
// declare linked list to connect allocation blocks
struct node{
   int id;
   int start;
   int end;
   struct node *link;
} *block_list = NULL;
typedef struct node block_type;
// declare global variables
int pm_size;
int hole_algo;
int remaining;
int best_so_far;

/********************************************************************/
void enterParams() {
	
	// declare local variables (if any)
	// prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory
   printf("Enter size of physical memory: ");
   scanf("%d", &pm_size);
   printf("%d\n", pm_size);
   remaining = pm_size;
   best_so_far = pm_size;
   printf("Enter hole-fitting algorithm (0=first fit, 1=best_fit): ");
   scanf("%d", &hole_algo);
   printf("%d\n", hole_algo);
   printf("\n");

	return;
}


/********************************************************************/
void printAllocation() { //"PROCEDURE TO PRINT ALLOCATION TABLE"
	block_type *next_block = block_list;
   printf("\n");
   printf("ID\tStart\tEnd\n");
   printf("---------------------\n");
	// declare local variables
   while(next_block != NULL){ 
	// print table containing block id, starting address, ending address
      printf("%d\t%d\t%d\n", next_block->id, next_block->start, next_block->end);
      next_block = next_block->link;
   }
   printf("\n");
	return;
}


/********************************************************************/
void allocate() {//option 2
	
	// declare local variables
   int block_id, block_size;
   block_type *new_block, *current_block, *best_block;
   int best_start, best_end;
   int hole_start, hole_end;
   int best_so_far = pm_size;//???????? check
   int large_enough_hole = 0;
	// prompt for block id & block size
   printf("Enter block id: ");
   scanf("%d", &block_id);
   printf("%d\n", block_id);
   printf("Enter block size: ");
   scanf("%d", &block_size);
   printf("%d\n", block_size);
	// check if size of block is larger than remaining unallocated space, if not, return
   if(block_size > remaining){	
      printf("Cannot fit block--not enough memory\n");
      return;
   }
	// allocate space for new block and set id
	new_block = (block_type *)malloc(sizeof(block_type));
   new_block->id = block_id;
	// if no current blocks, insert block at front of linked list, set fields, return
	if (block_list == NULL) {
      new_block->start = 0;
      new_block->end = block_size;
      new_block->link = NULL;	
      block_list = new_block;
      printAllocation();
      return;
   }
	// else traverse list until either appropriate hole is found or the end of the list is reached
   //else(){
      current_block = block_list;
      while(current_block != NULL){
			// if id already exists, reject request and return
         if (block_id == current_block->id){
            printf("Duplicate id\n");
            return;
         }
			// set values for start and end of currently found hole
         hole_start = current_block->end;
         if(current_block->link != NULL){
            hole_end = current_block->link->start;
         }
         else{
            hole_end = pm_size;
         }
			// if hole is large enough for block
         if(block_size <= (hole_end - hole_start)){
               large_enough_hole = 1;
					// if first-fit algorithm
               if(hole_algo == 0){
							// set start & end fields of new block & add block into linked list
                     new_block->start = hole_start;
                     new_block->end = hole_start + block_size;
                     remaining -= block_size;
							// reduce remaining available memory and return
                     //printAllocation();
                     return;
				   }

					// else--best-fit algorithm
               else{
							// if hole is smaller than best so far
                     if((hole_end - hole_start) < best_so_far){
                           best_so_far = hole_end - hole_start;
                           best_start = hole_start;
                           best_end = hole_end;
                           best_block = current_block;
									// set values of best start & best end & best hole size so far
									// update best block & advance next block
                     } 
               }//else
	      }//if hole is large enough
         current_block = current_block->link;
         
    }//while	
    if(large_enough_hole == 0){
      printf("Cannot fit block--no hole large enough\n");
      return;
    }   
	//printAllocation(); possible solution to issue or after remaining -=
   // set start & end fields of new block & add block into linked list 
   new_block->start = best_start;	
   new_block->end = best_start + block_size;
   new_block->link = best_block->link;
   best_block->link = new_block;   
	// reduce remaining available memory and return
   remaining -= block_size;
   printAllocation();
	return;	
}
	

/********************************************************************/
void deallocate() {//option 3
	// declare local variables
	block_type *current_block = block_list;
   block_type *prev_block;
   int block_id;//????
   if (current_block == NULL){
      printf("Memory is empty--nothing to deallocate\n");
      return;
   }
	// prompt for block id
   printf("Enter block id: ");
   scanf("%d", &block_id);
   printf("%d\n", block_id);
   current_block = block_list;
	// until block id is found or end of linked list is reached
   while((current_block != NULL) && (block_id != current_block->id)){
		// traverse list
      prev_block = current_block;
      current_block = current_block->link;
	}
	// if end of linked list reached, print block id not found
	if(current_block == NULL){
      printf("Block id not found");
   }
	// else remove block and deallocate memory
   else{
      prev_block->link = current_block->link;
      remaining += current_block->end - current_block->start;
      best_so_far += remaining;
      free(current_block);
   }
   printAllocation();
	return;
}


/********************************************************************/
void defragment() {//option 4
	// declare local variables 	   
   block_type *current_block;
   int current_size;
   int prev_end=0;
   current_block = block_list;
	// until end of list is reached
   while(current_block != NULL){
			// calculate current hole size
         current_size = current_block->end - current_block->start;
         current_block->start = prev_end;
         current_block->end = current_block->start + current_size;
         prev_end = current_block->end;
			// adjust start & end fields of current block to eliminate hole
         current_block = current_block->link;
   }
   printAllocation();
	return;
}


/********************************************************************/
void OPTION5() {//option 5 (parameter_type *node)
	
	// if node is NULL, return
	// else
		//recursively call procedure on node->link
		// deallocate memory from node
	return;
}


/***************************************************************/
void printMenu(){
	int choice;
	do{
		choice = 0;
      printf("Memory allocation strategies\n");
      printf("----------------------------\n");
      printf("1) Enter parameters\n");
      printf("2) Allocate memory for block\n");
      printf("3) Deallocate memory for block\n");
      printf("4) Defragment memory\n");
      printf("5) Quit program\n");
      printf("\nEnter selection: ");
		scanf("%d", &choice);
      printf("%d\n", choice);
		switch(choice){
			case 1:
				enterParams();
				break;
			case 2:
				allocate();
				break;
         case 3:
            deallocate();
				break;
         case 4:
            defragment();
				break;
         case 5:
            exit_program();
				break;
			default:
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;	
		}
	}while(choice != 5);
}


int main() {
	/* Declare local variables */	
	/* Until the user quits, print the menu, get user's choice, call the appropriate procedure */
	printMenu();
   return 1;
}

void exit_program(){
   printf("Quitting program\n");
   exit(0);
}

