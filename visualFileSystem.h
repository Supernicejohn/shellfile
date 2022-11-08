#include "structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>

#define FILENAME_LEN 256  // max filename length
#define VFS_SORT_NAME 1
#define VFS_SORT_TYPENAME 2

struct viewArea *newViewArea(int,int,int,int);
int isNavigationDirectory(const char *);
int getDirectoryItemCount(const char *);
struct visualDirectory *newVisualDirectory(const char *);
void destroyDirectory(struct visualDirectory *);
void sortVisualDirectory(struct visualDirectory *, int);
struct visualDirectory *getDirectoryEntries(const char *);
void gotoCurrentDirectory(struct directoryHierarchy *);
int setCurrentWorkingDirectory(struct directoryHierarchy *);
void shiftDirectoryHierarchy(struct directoryHierarchy *, int);
int getPreviousItemIndex(struct directoryHierarchy *, int);
void buildIndexPath(struct directoryHierarchy *);
