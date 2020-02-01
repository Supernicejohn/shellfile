#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "keyboardHelper.h"

#define FILENAME_LEN 256  // max filename length

struct visualDirectory {
	char **itemNames;
	int nItems;
	char *itemTypes;
};

int isNavigationDirectory(const char *d_name){
	// TODO: make this better.
	if (strcmp(d_name,".")==0 || strcmp(d_name,"..")==0){
		return 1;
	}
	else {
		return 0;
	}
}
int getDirectoryItemCount(const char *dirPath){
	DIR *directory = opendir(dirPath);
	struct dirent *dEntries;
	if (directory == NULL){
		return -1;
	}
	int nItems = 0;
	while ((dEntries = readdir(directory))){
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
		while ((dEntries = readdir(directory))){
			strncpy(visDir->itemNames[index],dEntries->d_name,FILENAME_LEN);
			DIR *tempDir;
			char *tempDirPath = calloc(1,1024);
			strcat(tempDirPath,dirPath);
			strcat(tempDirPath,"/");
			strcat(tempDirPath,dEntries->d_name);
			printf("\n%s\n",tempDirPath);
			visDir->itemTypes[index] = (tempDir = opendir(tempDirPath)) ? 'd' : 'f';
			if (tempDir != NULL){
				closedir(tempDir);
			}
			
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
	printf("\n");
	for (int i=0; i<visDir->nItems/nColumns; i++){
		for (int j=0; j<nColumns;){
			if (index < visDir->nItems){
				if (!isNavigationDirectory(visDir->itemNames[index])){
					//print formatted
					printf("%s:%c; ",visDir->itemNames[index], visDir->itemTypes[index]);
					j++;
				}
				else {
					
				}
				index++;
			} 
			else {
				return;
			}

		}
		printf("\n");
	}

}







int main(int nStartOptions, char **startOptions){
	char *startDirectory = calloc(sizeof(char),1024);
	for (int i=0; i<nStartOptions; i++){
		//printf("\n%s\n",startOptions[i]);
	}
	if (nStartOptions > 1){
		strcpy(startDirectory,startOptions[1]);
	}
	else {
		getcwd(startDirectory,1024);
	}
	struct visualDirectory *visDir = getDirectoryEntries(startDirectory);
	for (int i=0; i<visDir->nItems; i++){
		//printf("%s\n",visDir->itemNames[i]);
	}

	displayDirectory(visDir,256,1);
	return 0;
}


