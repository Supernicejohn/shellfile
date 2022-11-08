#include "visualFileSystem.h"

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
void swapEntries(struct visualDirectory *visDir, int one, int two){
	char *name = calloc(sizeof(char),FILENAME_LEN);
	char type;
	strncpy(name,visDir->itemNames[one],FILENAME_LEN);
	memset(visDir->itemNames[one],0,FILENAME_LEN);
	strncpy(visDir->itemNames[one],visDir->itemNames[two],FILENAME_LEN);
	strncpy(visDir->itemNames[two],name,FILENAME_LEN);
	free(name);
	type = visDir->itemTypes[one];
	visDir->itemTypes[one] = visDir->itemTypes[two];
	visDir->itemTypes[two] = type;
}
void sortVisualDirectory(struct visualDirectory *visDir, int sortType){
	for (int i=0; i<visDir->nItems*10; i++){ // lazy sort. TODO: get a better one
		for (int j=0; j<visDir->nItems-1; j++){
			char *a = calloc(sizeof(char),FILENAME_LEN), *b = calloc(sizeof(char),FILENAME_LEN);
			strcpy(a,visDir->itemNames[j]);
			strcpy(b,visDir->itemNames[j+1]);
			for (int i=0; i<FILENAME_LEN; i++){
				a[i] = tolower(a[i]);
				b[i] = tolower(b[i]);
			}
			char c = visDir->itemTypes[j], d = visDir->itemTypes[j+1];
			switch(sortType){
				case VFS_SORT_NAME:
					if (strcmp(a,b)>0){
						swapEntries(visDir,j,j+1);
					}
					break;
				case VFS_SORT_TYPENAME:
					if (isNavigationDirectory(b) && !isNavigationDirectory(a)){
						swapEntries(visDir,j,j+1);
					}
					else if (d == 'd' && c != 'd'){
						swapEntries(visDir,j,j+1);
					}
					else if (strcmp(a,b)>0 && !(d != c && (d == 'd' || c =='d'))){
						swapEntries(visDir,j,j+1);
					}
					break;
				default:
					return;
			}
		}
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
	sortVisualDirectory(visDir,VFS_SORT_TYPENAME);
	return visDir;
}
void gotoCurrentDirectory(struct directoryHierarchy *dirHier){ // when 'g' is pressed, make the current folder the base folder.
	struct visualDirectory *visDir = dirHier->visDirs[dirHier->selectedDepth];
	for (int i=0; i<dirHier->depth; i++){
		if (i!=dirHier->selectedDepth){
			destroyDirectory(dirHier->visDirs[i]);
		}
	}
	dirHier->selectedDepth = 0;
	dirHier->depth = 1;
	dirHier->visDirs[0] = visDir;
}
int setCurrentWorkingDirectory(struct directoryHierarchy *dirHier){
	char *path = calloc(sizeof(char),FILENAME_LEN);
	//return chdir(dirHier->visDirs[dirHier->depth-1]->absolutePath);	
	return 0;
}
void shiftDirectoryHierarchy(struct directoryHierarchy *dirHier, int shiftRight){
	if (shiftRight){
		for (int i=dirHier->depth; i>0; i--){
			dirHier->visDirs[i] = dirHier->visDirs[i-1];
			dirHier->selectedIndexPath[i] = dirHier->selectedIndexPath[i-1];

		}
		dirHier->visDirs[0] = NULL;
		dirHier->selectedIndexPath[0] = -1;
		dirHier->depth++;
	}
}
int getPreviousItemIndex(struct directoryHierarchy *dirHier, int index){
	char *thisName = calloc(sizeof(char),1024);
	strcpy(thisName,dirHier->visDirs[index]->absolutePath);
	if (strlen(thisName)<=1){
		free(thisName);
		return -1;
	}
	for (int i=strlen(thisName)-2; i>=0; i--){
		if (thisName[i]=='/'){

			char *temp = calloc(sizeof(char),1024);
			strcpy(temp,thisName);
			memset(thisName,0,1024);
			strcpy(thisName,&temp[i+1]);
			free(temp);
		}
	}
	for (int i=0; i<dirHier->visDirs[index-1]->nItems; i++){
		if (strcmp(dirHier->visDirs[index-1]->itemNames[i],thisName)==0){
			printf("\n\n%s\n\n",thisName);
			
			free(thisName);
			return i;
		}
	}
	free(thisName);
	return -1;
}
void buildIndexPath(struct directoryHierarchy *dirHier){
	for (int n=0; n<dirHier->depth-2; n++){
		dirHier->selectedIndexPath[n]=getPreviousItemIndex(dirHier,n+1);
	}
	dirHier->selectedDepth = dirHier->depth-1;
}









