#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declare global variables
void exit_program();
int *sequence = NULL;
int num_tracks, sequence_size, algo;
/*******************************************/
void enterParams() {
	// prompt for number of concentric tracks, size of sequence, and scheduling algorithm
   printf("Enter number of concentric tracks: ");
   scanf("%d", &num_tracks);
   printf("%d\n", num_tracks);
   
   printf("Enter size of sequence: ");
   scanf("%d", &sequence_size);
   printf("%d\n", sequence_size);

   
   printf("Enter scheduling algorithm (0=FIFO, 1=SSTF): ");
   scanf("%d", &algo);
   printf("%d\n", algo);
   printf("\n");
   if(sequence != NULL){
      free(sequence);
   }
	// allocate memory for sequence dynamic array
   sequence = (int *)malloc(sequence_size * sizeof(int)); 
	return;
}


/*******************************************/
void schedule() {
	// declare local variables */
   int i,j;
   int temp;
   int traversed;
   int *sorted;
   int total_delay = 0;
   float average_delay = 0.0;
   int num_tracks_moved = 0;
   int longest_delay = 0;
   int longest_track = 0;
   int num_moves_right = 0;
   // for-loop: prompt for each track in sequence
   printf("Enter sequence of tracks to seek: ");
   for(i=0;i < sequence_size; i++){
      scanf("%d", &sequence[i]);
      printf("%d ", sequence[i]);
		// if track is out of range (<0 or > number of tracks, printe message and return
      if (sequence[i] <0 || sequence[i] > num_tracks){
         printf("Out of range!");
         return;
      }
   }
	// If FIFO
   if (algo==0){
      printf("\nTraversed sequence: ");
      for(i=0;i <= sequence_size-1;i++){ 
         printf("%d ", sequence[i]);
      }
		// initilize number of traversed tracks to first track in sequence
      traversed = sequence[0];
		// for loop:
      for(i=0;i <= sequence_size-1;i++){ 
			// update nummber of trversed tracks based on absolute value of difference between adjacent indices in sequence 
         traversed += abs(sequence[i] - sequence[i-1]);
      }
			// print traversed sequence
         printf("\nThe number of tracks traversed is: %d\n", (traversed-1));	
		// print number of traversed tracks 	
   } 
	// Else SSTF
   else{
		// allocate memory for sorted sequence dynamic array & initialize to original sequence
      sorted = (int *)malloc(sequence_size * sizeof(int));
      for(i=0; i < sequence_size; i++){
         sorted[i] = sequence[i];
      }
		// sort elements in increasing order using a sorting algorithm (Selection sort, etc.)
      for(i = 0; i < sequence_size;i++){
         int smallestIndex = i;
         for(j = i + 1; j< sequence_size; j++){
            if(sorted[j] < sorted[smallestIndex]){
               smallestIndex = j;
            }
         }
         temp = sorted[i];
         sorted[i] = sorted[smallestIndex];
         sorted[smallestIndex] = temp;
      }
      
		// for-loop: 
      for(i=0; i < sequence_size-1; i++){ 
         j = i+1;
         num_moves_right = 0;
         while((j < sequence_size) && (sequence[i] != sorted[j])){
            j++;
         }
         if(j < sequence_size){
            num_moves_right = j - 1;
            total_delay += num_moves_right;
            num_tracks_moved++;
            if(num_moves_right > longest_delay){
               longest_delay = num_moves_right;
               longest_track = sequence[i];
            }  
         }
			// calculate delays based on difference between track position in sorted array and original array
			// update value of longest delay if number of moved positions is greater than current longest delay		
		// initilize number of traversed tracks to first track in sequence
		}
      // for loop: 
      printf("\nTraversed sequence: ");
      for(i=0; i <= sequence_size - 1; i++){
			// update nummber of trversed tracks based on absolute value of difference between adjacent indices in sequence 
			// print traversed sequence
         printf("%d ", sorted[i]);	
      }
		// print number of traversed tracks 	
		// calculate and print average_delay
      average_delay = total_delay / num_tracks_moved;
      average_delay -= 1;
        // print longest delay
      longest_delay -= 1;
      longest_track -= 1;
      printf("\nThe average delay of all tracks processed later is: %.1f\n", average_delay);
      printf("The longest delay experienced by a track is: %d by track %d\n", longest_delay, longest_track);
      free(sorted);
	}
   printf("\n");
   return;
} 
		
	
/***************************************************************/
void option3() {
	// if sequence is not NULL, free sequence
	return;
} // 


/***************************************************************/
void printMenu(){
	int choice;
	do{
		choice = 0;
      printf("Disk scheduling\n");
      printf("---------------\n");
      printf("1) Enter parameters\n");
      printf("2) Schedule disk tracks\n");
      printf("3) Quit program\n");
      printf("\nEnter selection: ");
		scanf("%d", &choice);
      printf("%d\n", choice);
		switch(choice){
			case 1:
				enterParams();
				break;
			case 2:
				schedule();
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


int main() {
	/* Declare local variables */	
	/* Until the user quits, print the menu, get user's choice, call the appropriate procedure */
	printMenu();
   return 1;
}

void exit_program(){
   printf("Quitting program...");
   exit(0);
}

