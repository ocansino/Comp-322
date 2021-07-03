#include <stdio.h>
#include <stdlib.h>

/*
Comp 322 Robert McIlhenny
Oscar Cansino
Assignment #3 Resource Allocation and the Banker's Algorithm
*/
void exit_program();

/* Declare dynamic arrays and global variables*/
int *resource_array = NULL;
int *allocation_array = NULL;
int *available_array = NULL;
int *maxClaim_array = NULL;
int *need_array = NULL;

int numResources;
int numProcesses;
/***********************************************************/
void printResourceArray() {
	/* declare local variables */
   int i;
	/* for loop: print each resource index */
   printf("\nResources: \n");
   for(i = 0; i < numResources; i++){
      printf("\tr%d", i);
   }
   printf("\n");
	/* for loop: print number of total units of each resource index */
   for(i = 0; i < numResources; i++){
      printf("\t%d", resource_array[i]);
   }
	printf("\n");
   return;
}


/***********************************************************/
void printAvailableResource(){
	/* declare local variables */
	/* for loop: print each resource index */
	/* for loop: print number of available units of each resource index */
   int i;
	/* for loop: print each resource index */
   printf("\nAvailable: \n");
   for(i = 0; i < numResources; i++){
      printf("\tr%d", i);
   }
   printf("\n");
	/* for loop: print number of total units of each resource index */
   for(i = 0; i < numResources; i++){
      printf("\t%d", available_array[i]);
   }
	printf("\n");
   return;

	//return;
}


/***************************************************************/
void printMaxClaimArray() { 
	/* declare local variables */
	/* for loop: print each resource index */
	/* for each process: */
		/* for each resource: */
			/* print maximum number of units each process may request from each resource */
   /* declare local variables */
   int i;
   int j;
   printf("\nMax claim:\n");
	/* for loop: print each resource index */
   printf("\t");
   for(i=0;i<numResources;i++){
      printf(" r%d ", i);
   }

	/* for each process: */
      for(i=0;i<numProcesses;i++){
         printf("\n\tp%d ", i);
		/* for each resource: */
         for(j=0;j<numResources;j++){
			/* print maximum number of units each process is allocated from each resource */
            printf("%d   ", maxClaim_array[i * numResources + j]);
         }
      }
   
	return;


	//return;
}


/***************************************************************/
void printAllocationArray() {
	/* declare local variables */
   int i;
   int j;
   printf("\nAllocated:\n");
	/* for loop: print each resource index */
   printf("\t");
   for(i=0;i<numResources;i++){
      printf(" r%d ", i);
   }

	/* for each process: */
      for(i=0;i<numProcesses;i++){
         printf("\n\tp%d ", i);
		/* for each resource: */
         for(j=0;j<numResources;j++){
			/* print maximum number of units each process is allocated from each resource */
            printf("%d   ", allocation_array[i * numResources + j]);
         }
      }
   
	return;
}

/***************************************************************/
void printNeedArray() {
	/* declare local variables */
	/* for loop: print each resource index */
	/* for each process: */
		/* for each resource: */
			/* print number of units needed by each process from each resource */
   /* declare local variables */
   int i;
   int j;
   printf("\nNeed:\n");
	/* for loop: print each resource index */
	printf("\t");
   for(i=0;i<numResources;i++){
      printf(" r%d ", i);
   }
	/* for each process: */
      for(i=0;i<numProcesses;i++){
         printf("\n\tp%d ", i);
		/* for each resource: */
         for(j=0;j<numResources;j++){
			/* print maximum number of units each process is allocated from each resource */
            printf("%d   ", need_array[i * numResources + j]);
         }
      }
   
	printf("\n");
   return;


	//return;
}


/****************************************************************/
void enterParams() { //option1
	/* declare local variables */
   int i;
   int units;
	/* prompt for number of processes and number of resources */
   printf("Enter number of processes: ");
   scanf("%d", &numProcesses);
   printf("%d\n", numProcesses);
   printf("Enter number of resources: ");
   scanf("%d", &numResources);
   printf("%d\n", numResources);
	/* allocate memory for arrays and arrays: resource, available, max_claim, allocated, need */
   resource_array = (int *)malloc(numResources * sizeof(int));
   available_array = (int *)malloc(numResources * sizeof(int));
   maxClaim_array = (int *)malloc(numProcesses * numResources * sizeof(int));
   allocation_array = (int *)malloc(numProcesses * numResources * sizeof(int));
   need_array = (int *)malloc(numProcesses * numResources * sizeof(int));
   
	/* for each resource, prompt for number of units, set resource and available arrays indices*/
   for(i=0;i<numResources;i++){
      printf("Enter number of units for resource r%d: ", i);
      scanf("%d", &units);
      printf("%d\n", units);
      resource_array[i] = units;
      available_array[i] = units;
   }
	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */
   for(i=0;i<numProcesses;i++){
      for(int j=0;j<numResources;j++){
         printf("Enter maximum number of units process p%d will request from resource r%d: ", i, j);
         scanf("%d", &units);
         printf("%d\n", units);
         maxClaim_array[i*numResources+j] = units;
         need_array[i*numResources+j] = units;
      }
   
   
   }
	/* for each process, for each resource, prompt for number of resource units allocated to process */
   for(i=0;i<numProcesses;i++){
      for(int j=0;j<numResources;j++){
         printf("Enter number of units resource r%d will request from process p%d: ", j, i);
         scanf("%d", &units);
         printf("%d\n", units);
         allocation_array[i*numResources+j] = units;
         need_array[i*numResources+j] -= units;
         available_array[j] -= units;
      }
   
   
   }

	/* call procedures to print resource array, available array, max_claim array, allocated array, need array */
   printResourceArray();
   printAvailableResource();
   printMaxClaimArray();
   printAllocationArray();
   printNeedArray();
	return;
}


/********************************************************************/
void safeSequence() { //option2
 
	/* declare local variables, including array to indicate if process is safely sequenced and "done" counter*/
   int done = 0;
   int lessThan;
   int j;
   int *sequenced = (int *)calloc(numProcesses, sizeof(int));
	/* while not done */
   while (done < numProcesses){
		/* for each process to check for safe sequencing */
         for(int i = 0; i<numProcesses;i++){
            lessThan = 1;
			/* if not already put in a safe sequence */
            if(sequenced[i] == 0){
				/* for each resource, print need array entry */
               printf("\nChecking p%d: < ", i);
               for(j=0;j<numResources;j++){
                  printf("%d", need_array[i*numResources+j]);
               }
               printf(" > <= < ");
				/* for each resource, print available array entry */
               for(j=0;j<numResources;j++){
                  printf("%d", available_array[j]);
               }
               printf(" > ");
				/* for each resource, check if need array entry is less than available array entry */
               for(j=0;j<numResources;j++){
                  lessThan = lessThan & (need_array[i*numResources+j] <= available_array[j]);
               }
				/* if all need entries are less than the corresponding available entry */ 
               if(lessThan == 1){
					/* put process in safe sequence*/
                    printf(" :p%d safely sequenced\n", i);
                    sequenced[i] = 1;
					/* for each resource */
                  for(j=0;j<numResources;j++){
						/* adjust units in available array */
                     available_array[j] += allocation_array[i*numResources+j];
                     allocation_array[i*numResources+j] = 0;
                     need_array[i*numResources+j] = maxClaim_array[i*numResources+j];
						/* reset units in allocated array */
                  
						/* increment "done" counter */
                  done++;
                  }
                  
               }//if
               //printf("");
            
           }
        }
        }
	     free(sequenced);
        printf("\n");
        return;
}


/********************************************************************/
void freeMemory() { //option 3
	/* free memory for all arrays and arrays is not NULL */
   
   exit_program();
	return;
}


/***************************************************************/
void printMenu(){
	int choice;
	do{
		choice = 0;
      printf("Resource Allocation\n");
      printf("--------------------------------\n");
      printf("1) Enter parameters\n");
      printf("2) Determine safe sequence\n");
      printf("3) Quit program\n");
      printf("\nEnter selection: ");
		scanf("%d", &choice);
      printf("%d\n", choice);
		switch(choice){
			case 1:
				enterParams();
				break;
			case 2:
				safeSequence();
				break;
         case 3:
            freeMemory();
				break;
			default:
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;	
		}
	}while(choice != 3);
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

