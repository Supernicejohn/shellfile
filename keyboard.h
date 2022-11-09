#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#define KEYS_NOKEY 0
#define KEYS_UP 1
#define KEYS_DOWN 2
#define KEYS_LEFT 3
#define KEYS_RIGHT 4
#define KEYS_ENTER 5
#define KEYS_BACKSPACE 6
#define KEYS_ESCAPE 7
#define KEYS_DELETE 8
#define KEYS_INSERT 9
#define KEYS_HOME 10
#define KEYS_END 11
#define KEYS_PAGEUP 12
#define KEYS_PAGEDOWN 13

char getKeyCode(int,int);
int isPrintable(char);
int getSpecialKey(char);
