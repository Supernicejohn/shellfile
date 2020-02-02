struct visualDirectory {
	char **itemNames;
	int nItems;
	char *itemTypes;
	char absolutePath[1024];
};
struct directoryHierarchy {
	struct visualDirectory *visDirs[10];
	int selectedIndexPath[10];
	int depth;
	int selectedDepth;
};
struct viewArea {
	int x,y;
	int w,h;
};


