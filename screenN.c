#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "structs.h"
#include <ncurses.h>

#define TERMCOL_BLACK 0
#define TERMCOL_RED 1
#define TERMCOL_GREEN 2
#define TERMCOL_YELLOW 3
#define TERMCOL_BLUE 4
#define TERMCOL_MAGENTA 5
#define TERMCOL_CYAN 6
#define TERMCOL_WHITE 7 // yeah ok "white" is just gray it seems like
#define TERMCOL_DEFAULT 9

#define TERMTEXT_NORMAL 0
#define TERMTEXT_BOLD 1
#define TERMTEXT_ITALIC 3
#define TERMTEXT_UNDERLINE 4
#define TERMTEXT_INVERT 7

int getTerminalWidth(){
	int x,y;
	getmaxyx(&y,&x);
	return x;
}
int getTerminalHeight(){
	int x,y;
	getmaxyx(&y,&x);
	return y;
}
void setCursorPosition(int,int);
void applyTerminalSettings(struct terminalSettings *);
void setTextColor(struct terminalSettings *, int);
void setBackgroundColor(struct terminalSettings *, int);
void setTextType(struct terminalSettings *, int);
void drawBox(struct viewArea *a, char c){
	mvvline(a->y,a->x,'-',a->w);
	mvvline(a->y+a->h-1,a->x,'-',a->w);
	mvhline(a->y,a->x,'|',a->h);
	mvhline(a->y,a->x+a->w-1,'|',a->h);
}
void clear(struct viewArea *a){
	for (int i=0; i<a->h; i++){
		mvvline(a->y+i,a->x,0,a->w);
	}
}
void printFullWidth(struct viewArea *a, const char *str){
	strnlen(str,200);
	char *buffer[] = calloc(size,sizeof(char);
	memset(buffer,0,200);
	strncpy(buffer,str,200);
	mvprintw(a->y,a->x,str);
}
