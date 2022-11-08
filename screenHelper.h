#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define TERMCOL_DEFAULT 9

#define TERMTEXT_NORMAL 0
#define TERMTEXT_BOLD 1
#define TERMTEXT_ITALIC 3
#define TERMTEXT_UNDERLINE 4
#define TERMTEXT_INVERT 7

int getTerminalWidth();
int getTerminalHeight();
void setCursorPosition(int,int);
void applyTerminalSettings(struct terminalSettings *);
void setTextColor(struct terminalSettings *, int);
void setBackgroundColor(struct terminalSettings *, int);
void setTextType(struct terminalSettings *, int);
void drawBox(struct viewArea *);
void clear(struct viewArea *);
void printFullWidth(struct viewArea *, const char *);
