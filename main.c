#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#include "keyboardHelper.h"

#define FILENAME_LEN 256  // max filename length

struct visualDirectory {
	char **itemNames;
	int nItems;
	char *itemTypes;
};

int getDirectoryItemCount(const char *dirPath){
	DIR *directory = opendir(dirPath);
	if (directory == NULL){
		return -1;
	}
	int nItems = 0;
	while (readdir(directory)){
		nItems++;
	}
	closedir(directory);
	return nItems;
}

struct visualDirectory *newVisualDirectory(const char *dirPath){
	struct visualDirectory *visDir = calloc(sizeof(struct visualDirectory),1);
	visDir->nItems = getDirectoryItemCount(dirPath);
	visDir->itemNames = calloc(sizeof(char*),visDir->nItems);
	visDir->itemTypes = calloc(sizeof(char),visDir->nItems);
	for (int i=0; i<visDir->nItems; i++){
		visDir->itemNames[i] = calloc(sizeof(char),FILENAME_LEN);
	}
	return visDir;
}
void destroyDirectory(struct visualDirectory *visDir){
	if (visDir != NULL){
		for (int i=0; i<visDir->nItems; i++){
			free(visDir->itemNames[i]);
		}
		free(visDir->itemTypes);
		free(visDir);
	}
}

// modified from source at gnu.org "https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Simple-Directory-Lister.html" (fetched 2020 January 31st)
struct visualDirectory *getDirectoryEntries(const char *dirPath){
	struct dirent *dEntries;
	DIR *directory = opendir(dirPath);
	struct visualDirectory *visDir = newVisualDirectory(dirPath);
	int index = 0;
	if (directory != NULL){
		while (dEntries = readdir(directory)){
			strncpy(visDir->itemNames[index],dEntries->d_name,FILENAME_LEN);
			visDir->itemTypes[index] = dEntries->d_type;
			
			index++;
		}
		closedir(directory);
	}
	else {
		return NULL;
	}
	return visDir;
}

void displayDirectory(struct visualDirectory *visDir, int filenameMaxLength, int nColumns){
	int index = 0;
	for (int i=0; i<visDir->nItems/nColumns; i++){
		for (int j=0; j<nColumns; j++){
			if (index < visDir->nItems){
				//print formatted
			}
		}
	}

}







int main(int nStartOptions, char **startOptions){
	char *startDirectory = calloc(sizeof(char),1024);
	for (int i=0; i<nStartOptions; i++){
		printf("\n%s\n",startOptions[i]);
	}
	if (nStartOptions > 1){
		strcpy(startDirectory,startOptions[1]);
	}
	else {
		strcpy(startDirectory,"/");
	}
	struct visualDirectory *test = getDirectoryEntries(startDirectory);
	for (int i=0; i<test->nItems; i++){
		printf("%s\n",test->itemNames[i]);
	}
	return 0;
}


