#define isFile 1
#define isFolder 0

typedef struct directories {

    int lineNumber; // Ir ao último (lineNumber-1)
    int fileOrFolder;
    char* name;
    char* directory;
    struct directories* next;

} Directories;

// Auxiliar Functions: countLine, cleanName, numberIterations and inserEnd
// Principal Function: insertDirectory
int countLines(char *lineName);
char* cleanName(char *name, char *rootName);
int numberIterations(Directories *list, int lineLimit);
Directories* insertEnd(Directories *list, int lN, int fileFolder, char *n, char *d);
Directories* insertDirectory(Directories* list, int fileFolder, char *fileName, char *rootName);

// Auxiliar Function: lastDirectory
// Principal Functions: createFolder, createFile
char* lastDirectory(Directories *list);
void createFolder(Directories *list);
void createFile(Directories *list);

// Other Functions
Directories* init();
char* getDirectory(Directories *list, char* nameFile);
void printDirectories(Directories *list);
