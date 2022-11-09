#include "screen.h"
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

void applyTerminalSettings(struct terminalSettings *ts){
	printf("\033[%d;%d;%dm",30+ts->textColor,40+ts->backgroundColor,ts->textModifiers);

}
void setTextColor(struct terminalSettings *ts, int color){
	ts->textColor = color;
}
void setBackgroundColor(struct terminalSettings *ts, int color){
	ts->backgroundColor = color;
}
void setTextType(struct terminalSettings *ts, int flags){
	ts->textModifiers = flags;
}

void drawBox(struct viewArea *vArea){
	//printf("\033[94;100m");
	struct terminalSettings ts;
	setTextColor(&ts,TERMCOL_BLACK);
	setBackgroundColor(&ts,TERMCOL_WHITE);
	applyTerminalSettings(&ts);
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			setCursorPosition(vArea->x+(vArea->w-1)*i,vArea->y+(vArea->h-1)*j);
			printf("+");
		}
	}
	for (int i=vArea->x+1; i<vArea->x+vArea->w-1; i++){
		// set top and bottom pixels background color
		setCursorPosition(i,vArea->y);
		printf("-");
		setCursorPosition(i,vArea->y+vArea->h-1);
		printf("-");
	}
	for (int i=vArea->y+1; i<vArea->y+vArea->h-1; i++){
		// set left and right pixels background color
		setCursorPosition(vArea->x,i);
		printf("|");
		setCursorPosition(vArea->x+vArea->w-1,i);
		printf("|");
	}
}
void clear(struct viewArea *vArea){
	struct terminalSettings ts;
	setTextColor(&ts,TERMCOL_BLACK);
	setBackgroundColor(&ts,TERMCOL_GREEN);
	applyTerminalSettings(&ts);
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









