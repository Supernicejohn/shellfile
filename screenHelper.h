#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "structs.h"

#define TERMCOL_BLACK 0
#define TERMCOL_RED 1
#define TERMCOL_GREEN 2
#define TERMCOL_YELLOW 3
#define TERMCOL_BLUE 4
#define TERMCOL_MAGENTA 5
#define TERMCOL_CYAN 6
#define TERMCOL_WHITE 7 // yeah ok "white" is just gray it seems like
//modified from answer by user John T on Stack Overflow (https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c)
int getTerminalWidth(){
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	return window.ws_col;
}
int getTerminalHeight(){
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	return window.ws_row;
}

void setCursorPosition(int x, int y){
	printf("\033[%d;%dH",y,x);
}

void setColor(int backgroundColor, int textColor){
	printf("\033[%d;%dm",30+textColor,40+backgroundColor);
}

void drawBox(struct viewArea *vArea){
	//printf("\033[94;100m");
	setColor(TERMCOL_BLACK,TERMCOL_WHITE);
	for (int i=vArea->x; i<vArea->x+vArea->w; i++){
		// set top and bottom pixels background color
		setCursorPosition(i,vArea->y);
		printf("-");
		setCursorPosition(i,vArea->y+vArea->h-1);
		printf("-");
	}
	for (int i=vArea->y+1; i<vArea->y+vArea->h; i++){
		// set left and right pixels background color
		setCursorPosition(vArea->x,i);
		printf("|");
		setCursorPosition(vArea->x+vArea->w-1,i);
		printf("|");
	}
}
void clear(struct viewArea *vArea){
	setColor(TERMCOL_BLACK,TERMCOL_GREEN);
	for (int j=vArea->y; j<vArea->h; j++){
		char *line = calloc(sizeof(char),vArea->w);
		memset(line,' ',vArea->w-1);
		printf("%s",line);
	}
}
void printFullWidth(struct viewArea *vArea, const char *text){
	char *str = calloc(sizeof(char),vArea->w+1);
	strcpy(str,text);
	for (int i=strlen(str); i<vArea->w; i++){
		strcat(str," ");
	}
	setCursorPosition(vArea->x,vArea->y);
	printf("%s",str);
}









