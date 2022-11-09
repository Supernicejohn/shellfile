#include "controls.h"
#include "structs.h"
#include "screen.h"
#include "keyboard.h"
#include "visualFileSystem.h"
void drawDirectory(struct directoryHierarchy *dirHier, int depth, struct viewArea *vArea){
	for (int i=0; i<dirHier->visDirs[depth]->nItems; i++){
		char *line = calloc(sizeof(char),vArea->w);
		struct terminalSettings ts;
		setBackgroundColor(&ts,TERMCOL_DEFAULT);
		setTextColor(&ts,TERMCOL_WHITE);
		setTextType(&ts,TERMTEXT_NORMAL);
		if (dirHier->visDirs[depth]->itemTypes[i]=='d'){
			setBackgroundColor(&ts,TERMCOL_CYAN);
			setTextType(&ts,TERMTEXT_ITALIC);
		}
		if (isNavigationDirectory(dirHier->visDirs[depth]->itemNames[i])){
			setBackgroundColor(&ts,TERMCOL_MAGENTA);
		}
		if (dirHier->selectedIndexPath[depth] == i){
			setTextColor(&ts,TERMCOL_RED);
			setTextType(&ts,TERMTEXT_BOLD);
		}

		applyTerminalSettings(&ts);
		strncpy(line,(dirHier->visDirs[depth])->itemNames[i],vArea->w);
		printFullWidth(newViewArea(vArea->x,vArea->y+i,vArea->w,vArea->h),line);
		free(line);
		setBackgroundColor(&ts,TERMCOL_DEFAULT);
		setTextColor(&ts,TERMCOL_DEFAULT);
		setTextType(&ts,TERMTEXT_NORMAL);
		applyTerminalSettings(&ts);
	}
}
void drawAll(struct directoryHierarchy *dirHier){
	int screenW = getTerminalWidth();
	int nAreas = dirHier->depth;
	int areaWidth = (screenW-1) / nAreas + 1;
	int maxHeight = 0;
	for (int i=0; i<dirHier->depth; i++){
		if (dirHier->visDirs[i]->nItems > maxHeight){
			maxHeight = dirHier->visDirs[i]->nItems+2;
		}
	}
	struct viewArea *vArea = newViewArea(1,1,areaWidth,maxHeight);
	clear(newViewArea(1,1,screenW,getTerminalHeight()));
	for (int i=0; i<nAreas; i++){
		drawBox(vArea);
		drawDirectory(dirHier,i,newViewArea(vArea->x+1,vArea->y+1,vArea->w-2,vArea->h-2));	
		vArea->x += areaWidth-1;
	}
	vArea->y = maxHeight;
	vArea->h = 1;
	vArea->x++;
	printFullWidth(vArea,"| h-left l-right j-down k-up | q-quit g-setbase |");
	free(vArea);
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
	struct directoryHierarchy *dirHier = calloc(sizeof(struct directoryHierarchy),1);
	dirHier->selectedIndexPath[0] = 0;
	
	
	dirHier->depth = 1;
	dirHier->visDirs[0] = visDir;
	dirHier->selectedDepth = 0;

	struct viewArea *vArea = newViewArea(0,0,30,30);
	while (1){
		drawAll(dirHier);
		doNavigation(dirHier);
		

	}
	setCursorPosition(0,0);
	printf("\033[0;0m");
	return 0;
}


