#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#include "keyboard.h"
#include "visualFileSystem.h"
#include "screen.h"
#include "structs.h"

char getItemType(struct directoryHierarchy *);
int getMovementKey(void);
void doNavigation(struct directoryHierarchy *);

