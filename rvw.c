/* 
# Family Name: Khalid
# Given Name: Aysar
# Section: Z
# Student Number: 209728866
# CSE Login: cse92028
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
          char word[101];
          int freq;
  } WordArray;

WordArray *dataset = NULL;
int num_elements = 0; // To keep track of the number of elements used
int num_allocated = 0; // This is essentially how large the array is

int AddToArray (WordArray word)
{
	if(num_elements == num_allocated) { // Are more refs required?
		
		// Feel free to change the initial number of refs and the rate at which refs are allocated.
		if (num_allocated == 0)
			num_allocated = 3; // Start off with 3 refs
		else
			num_allocated *= 2; // Double the number of refs allocated
		
		// Make the reallocation transactional by using a temporary variable first
		void *_tmp = realloc(dataset, (num_allocated * sizeof(WordArray)));
		
		// If the reallocation didn't go so well, inform the user and bail out
		if (!_tmp)
		{ 
			fprintf(stderr, "ERROR: Couldn't realloc memory!\n");
			return(-1); 
		}
		
		// Things are looking good so far, so let's set the 
		dataset = (WordArray*)_tmp;	
	}
	
	// Next we need to check if the word is already in the array
	int i;
	for(i=0;i<num_elements;i++){
		if (strcmp(dataset[i].word,word.word) == 0){
			//word is already in the list so we must increment
			//frequency of the current word at i
			dataset[i].freq++;
			return num_elements;
		}
	}
	//add the word to the array since we couldn't find it
	dataset[num_elements] = word; 
	num_elements++;	
	return num_elements;
}

//this is our comparison function for qsort, it allows us
//to comapre dataset elements between each other based on their frequency
int compare(WordArray *a,WordArray *b) 
{
  if (a->freq < b->freq)
      return 1;
   else if (a->freq > b->freq)
      return -1;
   else
      return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Please provide a file name as a command line argument.\n");
	}else{
	int fileCounter = 1;
	while(argc > fileCounter){
		
		char *ptr_filename = argv[fileCounter];
		printf("%s ", ptr_filename);
		
		FILE *ptr_file;
		char line[1000];
		ptr_file = fopen(ptr_filename, "r");

		if (!ptr_file){
			printf("File not found.\n");
			return 1;
		}
		char *word = NULL;
		while (fgets(line,1000, ptr_file) != NULL){

				//lets check if the line buffer has the new line character
				//if it does, then we need to replace it null char
				size_t newLineLength = strlen(line);
				if (line[newLineLength - 1] == '\n') line[newLineLength - 1] = '\0';

				//now lets split up the line to extract the words
				word = strtok(line, " ");
				while (word != NULL ){
					//we now create a temporary WordArray to store the word and its frequency
					//and then we add it to the array
					WordArray temp;
					strncpy(temp.word, word, strlen(word) + 1);
					temp.freq = 1;
					if (AddToArray(temp) == -1){
						printf("There was an error when adding a word to the array.\n");
						return 1;				
					}
					word = strtok(NULL, " " );
				}
		}

		qsort((void *) dataset,num_elements,sizeof(WordArray),compare);

		//print out most frequency word
		printf("%s %d \n", dataset[0].word,dataset[0].freq);
		fclose(ptr_file);
		
		WordArray *dataset = NULL;
		num_elements = 0;
		num_allocated = 0;
		
		fileCounter++;
	  }
	
		//deallocating memory used
		free(dataset);
	  return 0;
	}
}
