/**
 * Author: P12214763
 *
 * This programs is made for educational purpose only.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/** 
 * global variable
 * 
 * table_size:	The default size of the array.
 * 
 * sec_hash:	The prime number to be used for d_hash_Fun2.
 */

int table_size = 49157;		//max array size 65000
int sec_hash = 11;
FILE *fp;
/* ------------------------------------------------------------------------------------ */

/** 
 * dictionary:
 * 		The main table where everything will be stored.
 * 
 * key:		The hash key generate for individual word.
 *
 * word:	Word stores any string that is less than 41 characters.
 * 
 * answer:	Answer stores definition of the word but has to less than 
 *
 * hash_node:	Is the pointer to the struct dictionary
 */
struct dictionary {
	int key;
	char word[MAX_WORD_SIZE];
	char answer[MAX_DESC_SIZE];
};

struct dictionary * hash_node;	//hash_node calloc of dic
/* ------------------------------------------------------------------------------------ */

/** 
 * d_hash_Fun1:
 *		Takes the key and return the index.
 *
 * key:		Is passed onto the function to create unique index for each entry.	
 *
 * Returns:	The index which is key % table_size;
 */
int d_hash_Fun1(int key) {
	int index = key % table_size;
	return index;
}
/* ------------------------------------------------------------------------------------ */

/** 
 * d_hash_Fun2:
 *		Makes second hash function.
 *
 * sec_hash:	Is global variable and a prime number.	
 *
 * Returns:	The index which is sec_hash - (key % sec_hash).
 */
int d_hash_Fun2(int key) { 
	int index = sec_hash - (key % sec_hash);
	return index;
}
/* ------------------------------------------------------------------------------------ */

/** 
 * d_hash_double:
 * 		The double hash function is achieved by combining fist and second hash  
 * 		function.
 * 
 * Returns:	The total value of fist and second hash function.
 */
int d_hash_double(int key) {
	return d_hash_Fun1(key)  + d_hash_Fun2(key);
}
/* ------------------------------------------------------------------------------------ */

/**
 * d_hash_key:
 * 		Generates key for every word.
 * 
 * Returns:	The key generated.
 */
int d_hash_key(const char *word) {
	int i;
	int off = 0;
	int h = 0;
	
	for(i=0; word[i] != '\0'; i++) {
		h = h*3 + word[off++];
	}
	
	return h;
}
/* ------------------------------------------------------------------------------------ */

/**
 * d_initialise():
 * 		Allocates memory for the table.
 */
void d_initialise() {
	hash_node = (struct dictionary *)malloc(table_size*sizeof(struct dictionary));
	
	printf("\n=================================================\n\t\tWelcome\n\n");
	printf("Please read the README file provided before using\n");
	printf("=================================================\n\n");	
	printf("Type in a word you'll like to know the meaning of\n");
}
/* ------------------------------------------------------------------------------------ */

/**
 * d_read_from_file:
 * 		Reads words and answer from the text files.
 * 
 *  Returns:	true (1) if the file was successfully imported into the
 *              dictionary.
 *              false (0) if the file was not successfully imported.
 */
int d_read_from_file(const char * filename) {
	
	char word[MAX_WORD_SIZE];	/* temp variable */
	char answer[MAX_DESC_SIZE];	/* temp variable */
	
	fp = fopen(filename, "r");
	//printf("key \t\tWord \t\t Answer\n");
		if (fp != NULL) {
			while (fscanf (fp, "%s %[^\n]", word, answer) > 1) {
				int wordKey = d_hash_key(word);
				int firstHash = d_hash_Fun1(wordKey);

				//int firstHash = d_hash_double(wordKey);
			
				hash_node[firstHash].key = wordKey;
				strcpy(hash_node[firstHash].word, word);
				strcpy(hash_node[firstHash].answer, answer);
				
				
				//printf("%i\t\t%s\t\t%s\n", firstHash, hash_node[firstHash].word, hash_node[firstHash].answer);
			}
		return 1;
	}
	else return 0;
}
/* ------------------------------------------------------------------------------------ */

/**
 * d_lookup:
 * 		Compares the key of word and typed word if equal returns the answer
 * 		if not returns the error message.
 * 
 * Returns:     true (1) if the word was found in the dictionary;
 *              false (0) if the word was not found in the dictionary.
 */
int d_lookup(const char * word, char * meaning) {
	int i;
	int key = d_hash_key(word);
	int firstHash = d_hash_Fun1(key);
	
	//int firstHash = d_hash_double(key);

	
	if (hash_node[firstHash].key == key) {
		strcpy(meaning,hash_node[firstHash].answer);
		return 1;
	}
	return 0;
}
/* ------------------------------------ END OF FILE ----------------------------------- */
