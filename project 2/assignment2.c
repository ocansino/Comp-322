#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
Comp 322 Robert McIlhenny
Oscar Cansino
Assignment #2 Producer Consumer Problem
*/
void exit_program();
void producer();
void consumer();

int bufferSize;
int fillSize;
int emptySize;
int numIterations = 0;
int s;
int e;
int f;
int next_in = 0;
int next_out = 0;
int *buffer = NULL;

void enterParams(){
      int choice = 0;
      
      //buffer size
      printf("Enter size of the buffer: ");
      scanf("%d", &choice);
      bufferSize = choice;
      printf("%d\n\n", bufferSize);
      
      buffer = (int *)calloc(bufferSize,sizeof(int));
      
      //max fill size
      printf("Enter maximum fill size: ");
      scanf("%d", &fillSize);
      printf("%d\n\n", fillSize);
      
      //max empty size
      printf("Enter maximum empty size: ");
      scanf("%d", &emptySize);
      printf("%d\n\n", emptySize);

      //num of iterations
      printf("Enter number of iterations: ");
      scanf("%d", &numIterations);
      printf("%d\n\n", numIterations);    
      
}

int p(int n) {
	/* Decrement "variable" if non-negative */
   if(n > 0){
      n--;
   }
	return n;
}

int v(int n) {
/* Increment "variable" if it is less than the size of the buffer */
   if(n < bufferSize){
      n++;
   }
	return n;
}

/***************************************************************/
void printBuffer() {
	/* Declare local variables */
	printf("Buffer=");
	/* Print each element in a for-loop */
   for(int i; i< bufferSize; i++){
      printf("%d", buffer[i]);
   }
   printf("\n");
	return;
}

void simulateBuffer(){
      clock_t pc;
      f=0;
      e =  bufferSize;
      for (int i = 0; i < numIterations; i++){
         pc = clock() % 2;
         if(pc == 0){
            producer();
            printBuffer();
         }
         else{
            consumer();
            printBuffer();
         }
      }
      return;
}

void producer(){
     clock_t k1 = clock() % fillSize + 1;
     
     for (int i = 0; i < k1; i++){ 
          if ( e > 0){
            e = p(e);
            buffer[next_in] = 1;
            
            next_in = (next_in + 1) % bufferSize;
            f = v(f);
          }
     }
     printf("P[%ld]: ", k1);
     
     return;
}

void consumer(){
     clock_t k2 = clock() % emptySize + 1;
     
     for (int i = 0; i < k2; i++){ 
          if ( f > 0){
            f = p(f);
            buffer[next_out] = 0;
            next_out = (next_out + 1) % bufferSize;
            e = v(e);
          }
     }
     printf("C[%ld]: ", k2);
     
     return;

}

void printMenu(){
	int choice;
	do{
		choice = 0;
      printf("Producer-Consumer problem\n");
      printf("--------------------------------\n");
      printf("1) Enter parameters\n");
      printf("2) Simulate on a shared circular buffer\n");
      printf("3) Quit program and free memory\n");
      printf("\nEnter selection: ");
		scanf("%d", &choice);
      printf("%d\n", choice);
		switch(choice){
			case 1:
				enterParams();
				break;
			case 2:
				simulateBuffer();
				break;
         case 3:
            exit_program();
				break;
			default:
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;	
		}
	}while(choice != 3);
}


/***************************************************************/
int main() {
	/*declare local vars */
	/* until user quits, print menu, prompt for user's choice, call appropriate procedure */
   printMenu();
   
	return 1;
}

void exit_program(){
   printf("Quitting program\n");
   exit(0);
}
