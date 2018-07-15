/*
  Name: rm-trash utility
  Environment: Linux based operating system
  Developers:  
  Resident: Lahore, Pakistan
  Language: GNU C
  Version: 1.0.0
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

//#include "rmutils.h"
//#include "urmutils.h"

#define DEFAULT_MODE 0700
#define MAX_BYTES 1024
#define MAX_CHARS 1024
#define DIR_NAME ".mdrm_temp"

extern int errno;
/*
 HELPER METHODS
*/
void loadHelp();
const char *concat(const char *s1, const char *s2);
const char getType(const char *source);
const char *getTypeName(char type);
const char *getOption(int argc, char *args[]);
/*
 FILE OPERATION METHODS PROTOTYPES
*/
int isFile(const char *filename);
int isRegularFile(const char *filename);
int isAvailableFile(const char *filename);
int secureRemoveFile(const char *filename);
int removeFile(const char *filename);
int getFile(const char *filename);
/*
 DIRECTORY OPERATION METHODS PROTOTYPES
*/
int makeTempDir(const char *dirname);
int isDirEmpty(const char *dirname);
int copyDirContent(const char *filepath);
int makeDirectory(const char *filepath);
int removeDir(const char *dirname);
int secureRemoveDir(const char *dirname);
void doMove(const char *filepath);
void doSecureRemove(const char *filepath);
/*
 GLOBAL VARIABLES
*/
int rv = 0;
char myPath[1024];
/*
 MAIN METHOD OF PROGRAM
*/
int main(int argc, char **args)
{
        errno = 0;
        int argCounter = argc;
        char choice;             // choice for interatice operation
        const char *option = ""; // getting option for multiple files and directories

        /*
   CREATING TEMP DIRECTORY TO MOVE FILES TEMPORARLY
  */
        DIR *dir = opendir(DIR_NAME);
        if (dir == NULL)
        {
                rv = makeTempDir(".mdrm_temp");
        }
        /*
   PROGRAM CONDITIONAL DRIVER STRUCTURE
  */
        if (argCounter == 1)
        {
                fprintf(stderr, "rm: missing operands\nTry 'rm --help' for more information.\n");
        }

        option = getOption(argCounter, args);
        // if option is available then argCounter --
        if (option[0] == '-')
                argCounter = argCounter - 1;
        if (strcmp(option, "--help") == 0)
        {
                loadHelp();
                exit(0);
        }
        // ITERATING THROUGH COMMAND-LINE argS
        for (int i = 1; i < argCounter; i++)
        {
                const char *arg = args[i];
                // removing single file/directory
                if (strcmp(option, "") == 0)
                {
                        if (getType(arg) == '-' || getType(arg) == 'b' || getType(arg) == 'c' || getType(arg) == 'l' || getType(arg) == 's' || getType(arg) == 'p')
                        {
                                rv = removeFile(arg);
                                if (i == argCounter)
                                        return 0;
                                if (rv == 0)
                                        continue;
                                else
                                        fprintf(stderr, "mdrm: cannot delete '%s' file or directory\n", arg);
                        }
                        // removing single directory
                        else if (getType(arg) == 'd')
                                fprintf(stderr, "mdrm: cannot remove '%s': Is a directory\n", arg);
                        exit(0);
                }
                // removing single file/directory
                if (strcmp(option, "-s") == 0)
                {
                        if (getType(arg) == '-' || getType(arg) == 'b' || getType(arg) == 'c' || getType(arg) == 'l' || getType(arg) == 's' || getType(arg) == 'p')
                        {
                                rv = secureRemoveFile(arg);
                                if (i == argCounter)
                                        return 0;
                                if (rv == 0)
                                        continue;
                                else
                                        fprintf(stderr, "mdrm: cannot delete '%s' file or directory\n", arg);
                        }
                        // removing single directory
                        else if (getType(arg) == 'd')
                                fprintf(stderr, "mdrm: cannot remove '%s': Is a directory\n", arg);
                }
                // removing single file recursively and interactively
                else if (strcmp(option, "-i") == 0)
                {
                        if (getType(arg) == '-' || getType(arg) == 'b' || getType(arg) == 'c' || getType(arg) == 'l' || getType(arg) == 's')
                        {
                                printf("mdrm: remove '%s' (Y|N)? ", getTypeName(getType(arg)));

                                while ((choice = getchar()) != '\n' && choice != EOF)
                                {
                                        if (choice == 'y' || choice == 'Y')
                                        {
                                                rv = removeFile(arg);
                                                if (i == argCounter)
                                                        return 0;
                                                if (rv == 0)
                                                        continue;
                                                else
                                                        fprintf(stderr, "mdrm: unable to delete file or directory\n");
                                        }
                                        else if ((choice == 'n' || choice == 'N'))
                                                continue;
                                        else
                                                fprintf(stderr, "mdrm: invalid option\n");
                                        if ((choice == 'n' || choice == 'N') && i == argCounter)
                                                return 0;
                                }
                        }
                        else if (getType(arg) == 'd')
                        {
                                printf("mdrm: remove 'directory' (Y|N)? ");
                                while ((choice = getchar()) != '\n' && choice != EOF)
                                {
                                        if (choice == 'y' || choice == 'Y')
                                        {
                                                rv = removeDir(arg);
                                                if (i == argCounter)
                                                        return 0;
                                                if (rv == 0)
                                                        continue;
                                                else
                                                        fprintf(stderr, "mdrm: unable to delete '%s' file or directory\n", arg);
                                        }
                                        else if ((choice == 'n' || choice == 'N'))
                                                continue;
                                        else
                                                fprintf(stderr, "mdrm: invalid option\n");
                                        if ((choice == 'n' || choice == 'N') && i == argCounter)
                                                return 0;
                                }
                        }
                        else
                                fprintf(stderr, "mdrm: cannot delete '%s' file\n", arg);
                }
                // Getting file
                else if (strcmp(arg, "-fg") == 0)
                {
                        if (isAvailableFile(arg) == 0)
                        {
                                rv = getFile(arg);
                                if (rv == 0)
                                        return 0;
                                else
                                {
                                        printf("urm: unable to locate %s file or directory\n", arg);
                                        return 0;
                                }
                        }
                        else
                        {
                                fprintf(stderr, "urm: unable to locate %s file or directory\n", arg);
                        }
                }
                // Getting file through interactive way
                else if (strcmp(option, "-ifg") == 0)
                {
                        printf("mdrm: restore file (Y|N)? ");
                        while ((choice = getchar()) != '\n' && choice != EOF)
                        {
                                if (choice == 'y' || choice == 'Y')
                                {
                                        rv = getFile(arg);
                                        if (i == argCounter)
                                                return 0;
                                        if (rv == 0)
                                                continue;
                                        else
                                                fprintf(stderr, "mdrm: unable to restore '%s' file or directory not found\n", arg);
                                }
                                else if ((choice == 'n' || choice == 'N'))
                                        continue;
                                else
                                        fprintf(stderr, "mdrm: invalid option\n");
                                if ((choice == 'n' || choice == 'N') && i == argCounter)
                                        return 0;
                        }
                }
                // removing directories recursively
                else if (strcmp(option, "-rd") == 0)
                {
                        if (getType(arg) == 'd')
                        {
                                rv = removeDir(arg);
                        }
                        else
                                fprintf(stderr, "mdrm: cannot delete '%s' file, invalid option '%s' \n", arg, option);
                }
                // removing directories sercurely && recursively
                else if (strcmp(option, "-rsd") == 0)
                {
                        if (getType(arg) == 'd')
                        {
                                rv = secureRemoveDir(arg);
                        }
                        else
                                fprintf(stderr, "mdrm: cannot delete '%s' file, invalid option '%s' \n", arg, option);
                }
                else
                {
                        fprintf(stderr, "mdrm: cannot delete '%s' file or directory not found\n", arg);
                }
        }
        return 0;
}
int makeTempDir(const char *dirname)
{
        rv = mkdir(dirname, DEFAULT_MODE);
        return rv;
}
int isFile(const char *filename)
{
        struct stat fs;
        rv = stat(filename, &fs);
        exit(0);
        if (rv == 0)
        {
                int t_mode = fs.st_mode;
                if (S_ISREG(t_mode))
                        return 0;
                return -1;
        }
        else
        {
                perror("stat");
                exit(rv);
        }
}
const char getType(const char *source)
{
        struct stat mystat;
        rv = stat(source, &mystat);
        if (rv == -1)
                fprintf(stderr, "mdrm: cannot find '%s' file or directory", source);
        mode_t mode = mystat.st_mode;
        if (S_ISDIR(mode))
                return 'd';
        else if (S_ISREG(mode))
                return '-';
        else if (S_ISLNK(mode))
                return 'l';
        else if (S_ISCHR(mode))
                return 'c';
        else if (S_ISBLK(mode))
                return 'b';
        else if (S_ISSOCK(mode))
                return 's';
        else if (S_ISFIFO(mode))
                return 'p';
        else
                return '?';
}
const char *getTypeName(char type)
{
        if (type == 'd')
                return "directory";
        else if (type == '-')
                return "regular file";
        else if (type == 'b')
                return "block special file";
        else if (type == 's')
                return "socket  file";
        else if (type == 'c')
                return "character special file";
        else if (type == 'l')
                return "symbolic link";
        else if (type == 'p')
                return "pipe file";
}
int isAvailableFile(const char *source)
{
        struct stat st = {0};
        rv = stat(concat(".mdrm_temp/", source), &st);
        //printf("%s: %d",concat(".mdrm_temp/",source),rv);
        return rv;
}
int getFile(const char *filename)
{
        if (isAvailableFile(filename) == 0)
        {

                struct stat mystat;
                char buff[MAX_CHARS];
                rv = stat(concat(".mdrm_temp/", filename), &mystat);
                int mode_t = mystat.st_mode;
                int fdf = open(concat(".mdrm_temp/", filename), O_RDONLY);
                int fds = open(filename, O_TRUNC | O_CREAT | O_RDWR, mode_t);
                if (fds == -1)
                        fprintf(stderr, "mdrm: unable to restore '%s' file or directory not found", filename);
                else
                {
                        while (1)
                        {
                                int byte_t = read(fdf, buff, MAX_BYTES);
                                if (byte_t <= 0)
                                {
                                        break; // file reading complete
                                }
                                write(fds, buff, byte_t);
                        }
                }
                close(fdf); // file descriptor
                close(fds); // file descriptor
                rv = remove(concat(".mdrm_temp/", filename));
                if (rv == -1)
                        fprintf(stderr, "mdrm: unable to restore '%s' file or directory not found", filename);
                else
                        return 0;
        }
        else
                return -1;
}
int removeFile(const char *filename)
{
        struct stat mystat;
        char buff[MAX_CHARS];
        rv = stat(filename, &mystat);
        int mode_t = mystat.st_mode;

        int fdf = open(filename, O_RDONLY);
        const char *newfile = concat(".mdrm_temp/", filename);
        int fds = open(newfile, O_TRUNC | O_CREAT | O_RDWR, mode_t);
        if (fds == -1)
        {
                fprintf(stderr, "rm: unable to remove file");
                exit(0);
        }
        else
        {
                while (1)
                {
                        int byte_t = read(fdf, buff, MAX_BYTES);
                        if (byte_t <= 0)
                        {
                                break; // file reading complete
                        }
                        write(fds, buff, byte_t);
                }
        }
        close(fdf); // file descriptor for original file
        close(fds); // file descriptor for trash file
        rv = remove(filename);
        if (rv == -1)
        {
                fprintf(stderr, "rm: unable to perform remove operation");
                return -1;
        }
        else
                return 0;
}
int secureRemoveFile(const char *filename)
{
        rv = remove(filename);
        if (rv == -1)
                fprintf(stderr, "rm: unable to perform secure remove operation");
        else
                return 0;
}

int isDirEmpty(const char *dirname)
{
        DIR *dp = opendir(dirname);
        int hasContent = 0;
        errno = 0;
        struct dirent *entry;
        if (dp == NULL)
        {
                fprintf(stderr, "mdrm: failed to remove '%s': No such file or directory", dirname);
                exit(0);
        }
        while (1)
        {
                entry = readdir(dp);
                if (entry != NULL && errno != 0)
                {
                        fprintf(stderr, "mdrm: failed to remove '%s': No such file or directory", dirname);
                        exit(0);
                }
                if (entry == NULL && errno == 0)
                {
                        break;
                }
                else
                {
                        //checck for hidden items
                        if (entry->d_name[0] == '.')
                                continue;
                        hasContent++;
                }
        }
        if (hasContent > 0)
                return -1;
        return 0;
        closedir(dp);
}
const char *concat(const char *s1, const char *s2)
{
        char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
        //in real code you would check for errors in malloc here
        strcpy(result, s1);
        strcat(result, s2);
        return result;
}

int removeDir(const char *dirname)
{
        doMove(dirname); // moving files into trash .mdrm_temp/
        rv = remove(dirname);
        return rv;
}
int secureRemoveDir(const char *dirname)
{
        doSecureRemove(dirname); // removing
        rv = remove(dirname);
        return rv;
}
void doMove(const char *filepath)
{
        DIR *dir;
        struct dirent *entry;
        if (!(dir = opendir(filepath)))
                return;
        makeDirectory(filepath);
        while ((entry = readdir(dir)) != NULL)
        {
                if (entry->d_type == DT_DIR)
                {
                        char path[1024];
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                continue;
                        snprintf(path, sizeof(path), "%s/%s", filepath, entry->d_name);
                        doMove(path);
                        remove(path); // removing sub-directory
                }
                else
                {
                        snprintf(myPath, sizeof(myPath), "%s/%s", filepath, entry->d_name);
                        copyDirContent(myPath); // on directory/ies content
                        remove(myPath);         // removing files recursively
                        
                }
        }
        closedir(dir);
}
void doSecureRemove(const char *filepath)
{
        DIR *dir;
        struct dirent *entry;
        if (!(dir = opendir(filepath)))
                return;
        while ((entry = readdir(dir)) != NULL)
        {
                if (entry->d_type == DT_DIR)
                {
                        char path[1024];
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                continue;
                        snprintf(path, sizeof(path), "%s/%s", filepath, entry->d_name);
                        doSecureRemove(path);
                        remove(path); // removing sub-directory
                }
                else
                {
                        snprintf(myPath, sizeof(myPath), "%s/%s", filepath, entry->d_name);
                        remove(myPath); // removing files recursively
                }
        }
        closedir(dir);
}
int copyDirContent(const char *filepath)
{
        struct stat mystat;
        char buff[MAX_CHARS];
        rv = stat(filepath, &mystat);
        int mode_t = mystat.st_mode;

        const char *binName = ".mdrm_temp/";

        int fdf = open(filepath, O_RDONLY);
        const char *newFilePath = concat(binName, filepath);
        int fds = open(newFilePath, O_TRUNC | O_CREAT | O_RDWR, mode_t);
        if (fds == -1)
        {
                fprintf(stderr, "mdrm: unable to remove file/directory");
                exit(0);
        }
        else
        {
                while (1)
                {
                        int byte_t = read(fdf, buff, MAX_BYTES);
                        if (byte_t <= 0)
                        {
                                break; // file reading complete
                        }
                        write(fds, buff, byte_t);
                }
        }
        close(fdf); // file descriptor for original file
        close(fds); // file descriptor for trash file
        return 0;
}
int makeDirectory(const char *dirpath)
{
        const char *binName = ".mdrm_temp/";
        const char *newPath = concat(binName, dirpath);
        struct stat st = {0};
        rv = 0;
        if (stat(newPath, &st) == -1)
        {
                rv = mkdir(newPath, 0700);
        }
        return rv;
}
const char *getOption(int argc, char *args[])
{
        for (int i = 1; i < argc; i++)
        {
                if (args[i][0] == '-')
                        return args[i];
        }
        return "";
}
void loadHelp()
{
        printf("\trm - remove files or dir ectories\n");
        printf("\trm [OPTION]... [FILE]...\n");
        printf("DESCRIPTION:\n");
        printf("\tThis manual page documents the GNU version of rm.  rm removes each specified file.  By default, it does not remove directories\n");
        printf("\tIf  the -I or --interactive=once option is given, and there are more than three files or the -r, -R, or --recursive are given,\n\tthen rm prompts the user for whether to proceed with the entire operation.\n\tIf the response is not affirmative, the  entire  command is aborted.\n");
        printf("\tOtherwise,  if a file is unwritable, standard input is a terminal, or the -i or --inter‐active=always option is given, rm prompts \n\t the user for whether to remove the file.\n\tIf the response is not affirmative,the file is skipped.\n\n");
        printf("OPTION:\n");
        printf("\tRemove (unlink) the FILE(s).\n");
        printf("\t-i     prompt before every removal\n");
        printf("\t-fg    getting file from trash_bin\n");
        printf("\t-s     secure removal\n");
        printf("\t-rsd   secure removal of directory/directories\n");
        printf("\t-ifg   prompt before getting file from trash_bin\n");
        printf("\t-rd    remove directories and their contents recursively\n");
}