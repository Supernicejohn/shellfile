#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#include "keyboardHelper.h"
#include "visualFileSystem.h"
#include "screenHelper.h"
#include "structs.h"

char getItemType(struct directoryHierarchy *);
int getMovementKey(void);
void doNavigation(struct directoryHierarchy *);

