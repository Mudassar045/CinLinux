#ifndef RM_HEADER_FILE
#define  RM_HEADER_FILE
int getDir(char *dirName);
int getFile(char *fileName);
int getFileType(char * fileName);
int moveFile(char *oldFilepath, char *newFilePath);
int moveDir(char *oldDirPath);
#endif
