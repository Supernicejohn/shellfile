#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>


#include "keyboardHelper.h"
#include "visualFileSystem.h"
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
			if (getItemType(dirHier) == 'd'){
				currentDepth++;
				dirHier->selectedIndexPath[currentDepth] = 0;
				
			}
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








