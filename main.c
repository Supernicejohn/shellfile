#include "controls.h"
void drawDirectory(struct directoryHierarchy *dirHier, int depth, struct viewArea *vArea){
	for (int i=0; i<dirHier->visDirs[depth]->nItems; i++){
		char *line = calloc(sizeof(char),vArea->w);
		if (dirHier->selectedIndexPath[depth] == i){
			setColor(TERMCOL_RED,TERMCOL_BLACK);
		}
		else if (isNavigationDirectory(dirHier->visDirs[depth]->itemNames[i])){
			setColor(TERMCOL_MAGENTA,TERMCOL_BLACK);
		}
		else if (dirHier->visDirs[depth]->itemTypes[i]=='d'){
			setColor(TERMCOL_CYAN,TERMCOL_BLACK);
		}
		else {
			setColor(TERMCOL_WHITE,TERMCOL_BLACK);
		}
		strncpy(line,(dirHier->visDirs[depth])->itemNames[i],vArea->w);
		//setCursorPosition(vArea->x,vArea->y+i);
		//printf("%s",line);
		printFullWidth(newViewArea(vArea->x,vArea->y+i,vArea->w,vArea->h),line);
		printf("\033[39;49m");
	}
}
void drawAll(struct directoryHierarchy *dirHier){
	int screenW = getTerminalWidth();
	int nAreas = dirHier->depth;
	int areaWidth = screenW / nAreas;
	struct viewArea *vArea = newViewArea(1,1,areaWidth,getTerminalHeight());
	for (int i=0; i<nAreas; i++){
		drawBox(vArea);
		drawDirectory(dirHier,i,newViewArea(vArea->x+1,vArea->y+1,vArea->w-2,vArea->h-2));	
		vArea->x += areaWidth-1;
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
//	struct visualDirectory *visDir2 = getDirectoryEntries(strcat(startDirectory,"/Documents"));	
//	struct visualDirectory *visDir3 = getDirectoryEntries(strcat(startDirectory,"/C"));
//	struct visualDirectory *visDir4 = getDirectoryEntries(strcat(startDirectory,"/shf"));
	struct directoryHierarchy *dirHier = calloc(sizeof(struct directoryHierarchy),1);
	dirHier->selectedIndexPath[0] = 0;
//	dirHier->selectedIndexPath[1] = 7;
//	dirHier->selectedIndexPath[2] = 3;
	
	
	dirHier->depth = 1;
	dirHier->visDirs[0] = visDir;
//	dirHier->visDirs[1] = visDir2;
//	dirHier->visDirs[2] = visDir3;
//	dirHier->visDirs[3] = visDir4;

	dirHier->selectedDepth = 0;

//	for (int i=0; i<visDir->nItems; i++){
		//printf("%s\n",visDir->itemNames[i]);
//	}
	struct viewArea *vArea = newViewArea(0,0,30,30);
	//tempFindFirst(dirHier,startDirectory);
	drawAll(dirHier);
	//drawBox(vArea);
	//displayDirectory(visDir,256,1);
	while (1){
		clear(newViewArea(0,0,getTerminalWidth(),getTerminalHeight()));
		drawAll(dirHier);
		doNavigation(dirHier);
		

	}
	setCursorPosition(0,31);
	printf("\033[39;49m");
	return 0;
}


