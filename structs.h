#ifndef SHF_STRUCTS
#define SHF_STRUCTS
struct visualDirectory {
	char **itemNames;
	int nItems;
	char *itemTypes;
	char absolutePath[1024];
};
struct directoryHierarchy {
	struct visualDirectory *visDirs[100];
	int selectedIndexPath[100];
	int depth;
	int selectedDepth;
};
struct viewArea {
	int x,y;
	int w,h;
};
struct terminalSettings {
	int backgroundColor;
	int textColor;
	int textModifiers;
};
#endif
