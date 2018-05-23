#ifndef RM_HEADER_FILE
#define  RM_HEADER_FILE
int getDir(char *dirname);
int getFile(char *filename);
int getFileType(char * filename);
int moveFile(char *oldFilepath, char *newFilePath);
int moveDir(char *oldDirPath);
int removeFile(char* filename);
int removeDir(char* dirname);
#endif