#ifndef RM_HEADER_FILE
#define  RM_HEADER_FILE
int removeDir(char *dirname);
int removeFile(char *filename);
int getFileType(char * filename);
int moveFile(char *filepath);
int moveDir(char *dirpath);
#endif
