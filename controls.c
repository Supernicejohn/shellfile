#include "controls.h"
char getItemType(struct directoryHierarchy *dirHier){
	if (dirHier->selectedDepth >= 0){
		return dirHier->visDirs[dirHier->selectedDepth]->itemTypes[dirHier->selectedIndexPath[dirHier->selectedDepth]];
	}
	return -1;
}


int getMovementKey(){
	char scan = getKeyCode(16,1); // wait 16 milliseconds for input
	//char special = getSpecialKey(scan);
	//if (special >= KEYS_UP && special <= KEYS_RIGHT){
	//	return special;
	//}
	if (isPrintable(scan)){
		return scan;
	}
	return KEYS_NOKEY;
}
void doNavigation(struct directoryHierarchy *dirHier){
	int currentDepth = dirHier->selectedDepth;	
	char movement = getMovementKey();
	//while (getMovementKey() != KEYS_NOKEY){
		// loop
	//}
	int a;
	switch(movement){
		case 'k':
			if (dirHier->selectedIndexPath[currentDepth]>0)
				dirHier->selectedIndexPath[currentDepth]--;
			break;
		case 'j':
			if (dirHier->selectedIndexPath[currentDepth]<dirHier->visDirs[currentDepth]->nItems-1)
				dirHier->selectedIndexPath[currentDepth]++;
			break;
		case 'h':
			if (currentDepth>0){
				dirHier->selectedIndexPath[currentDepth] = -1;
				currentDepth--;
				dirHier->depth--;
			}
			break;
		case 'l':
			if (getItemType(dirHier) == 'd' && currentDepth < 99){
				currentDepth++;
				dirHier->selectedIndexPath[currentDepth] = 0;
				
			}
			break;
		case 'r':
			while(strcmp(dirHier->visDirs[0]->absolutePath,"/")!=0){
				printf("%s\n",dirHier->visDirs[0]->absolutePath);
				shiftDirectoryHierarchy(dirHier,1);
				char *path = calloc(sizeof(char),1000);
				strcpy(path,dirHier->visDirs[1]->absolutePath);
				printf("\n\n%s\n\n",path);
				for (int i=strlen(path)-1; i>=0; i--){
					if (path[i-1]=='/'){
						path[i] = 0;
						break;
					}
					path[i] = 0;
				}
				dirHier->visDirs[0] = getDirectoryEntries(path);
				free(path);
				buildIndexPath(dirHier);
			}
			break;	
		case 't':
			buildIndexPath(dirHier);
			break;
		case 'g':
			gotoCurrentDirectory(dirHier);
			currentDepth = dirHier->selectedDepth;
			break;
		case 's':
			a = setCurrentWorkingDirectory(dirHier);
			setCursorPosition(1,1);
			printf("%d %s",a,dirHier->visDirs[currentDepth]->absolutePath);
			exit(0);
			break;
		case 'q':
			printf("\033[0;0m");
			clear(newViewArea(0,0,getTerminalWidth(),getTerminalHeight()));
			setCursorPosition(1,1);
			exit(0);
			break;
	}

	if (dirHier->selectedDepth < currentDepth && getItemType(dirHier)){
		char *newPath = calloc(sizeof(char),1024);
		strcpy(newPath,dirHier->visDirs[dirHier->depth-1]->absolutePath);
		strcat(newPath,"/");
		strcat(newPath,dirHier->visDirs[dirHier->depth-1]->itemNames[dirHier->selectedIndexPath[currentDepth-1]]);
		dirHier->visDirs[dirHier->depth] = getDirectoryEntries(newPath);
		dirHier->selectedIndexPath[dirHier->depth] = 0;
		dirHier->depth++;
//		setCursorPosition(3,50);
//		printf("%s                                              ",newPath);
	}
	dirHier->selectedDepth = currentDepth;
}








