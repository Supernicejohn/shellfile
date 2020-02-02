#include "screenHelper.h"

#define FILENAME_LEN 256  // max filename length

struct viewArea *newViewArea(int x, int y, int w, int h){
	struct viewArea *vArea = calloc(sizeof(struct viewArea),1);
	vArea->x = x;
	vArea->y = y;
	vArea->w = w;
	vArea->h = h;
	return vArea;
}

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
	while ((readdir(directory))){
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
	memset(visDir->absolutePath,0,512);
	strcpy(visDir->absolutePath,dirPath);
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
			char *tempText = calloc(sizeof(char),1000);
			strcpy(tempText,dirPath);
			strcat(tempText,"/");
			strcat(tempText,dEntries->d_name);
			DIR *temp = opendir(tempText);
			if (temp != NULL){
				visDir->itemTypes[index] = 'd';
				closedir(temp);
			}
			else {
				visDir->itemTypes[index] = 'f';
			}
			free(tempText);
			index++;
		}
		closedir(directory);
	}
	else {
		return NULL;
	}
	return visDir;
}















