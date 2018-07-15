/*
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BYTES 1024
#define MAX_CHARS 1024

static const char *concat(const char *s1, const char *s2);
char **getDirContent(char *dirname, int content_count);
int getDirContentCount(char *dirname);
int copyContent(char *dirpath, char *filename);
int makeDirectory1(char *dirname, int mode_t);
int isRegFile(char *source);
int isDir(char *source);

int removeDir(char *dirname)
{
        char **dirContentArr = NULL; // array of directory contents
        struct stat statdir;
        int rv = stat(dirname, &statdir);
        int mode_t = statdir.st_mode;
        const char *newDirPath = concat(".mdrm_temp/", dirname);
        if (makeDirectory1(newDirPath, mode_t) == 0)
        {
                int content_count = getDirContentCount(dirname);
                dirContentArr = getDirContent(dirname, content_count);
                for (int i = 0; i < content_count; i++)
                {
                        char *src = dirContentArr[i];
                        if (isRegFile(src) == 0)
                        {
                                int rv = copyContent(newDirPath, src);
                                if (rv == -1)
                                {
                                        break;
                                }
                        }
                }
                // deallocating memory
                for (int i = 0; i < content_count; i++)
                {
                        free(dirContentArr[i]);
                }
                return 0;
        }
        else
        {
                fprintf(stderr,"mdrm: cannot remove '%s' directory\n",dirname);
                return 0;
        }
}
int makeDirectory1(char *dirname, int mode_t)
{
        struct stat st = {0};
        int rv = 0;
        if (stat(dirname, &st) == -1)
        {
               rv = mkdir(dirname, 0700);
        }
        return rv;
}
int copyContent(char *dirpath, char *filename)
{
        struct stat mystat;
        char buff[MAX_CHARS];
        int rv = stat(filename, &mystat);
        int mode_t = mystat.st_mode;

        int fdf = open(filename, O_RDONLY);
        char *newFilePath = concat(dirpath, filename);
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
char **getDirContent(char *dirname, int content_count)
{
        char **dirContentArr = (char **)malloc(sizeof(char *) * (content_count));
        DIR *dp = opendir(dirname);
        int errno = 0;
        int k = 0;
        struct dirent *entry;
        while (1)
        {
                entry = readdir(dp);
                if (entry != NULL && errno != 0)
                {
                        perror("mdrm: unable to remove directory");
                        exit(errno);
                }
                if (entry == NULL && errno == 0)
                {
                        break;
                }
                else
                {
                        if (entry->d_name[0] == '.')
                                continue;
                        dirContentArr[k] = (char *)malloc(sizeof(char) * (strlen(entry->d_name) + 1));
                        strcpy(dirContentArr[k++], entry->d_name);
                }
        }
        return dirContentArr;
}
int getDirContentCount(char *dirname)
{
        DIR *dp = opendir(dirname);
        int errno = 0;
        int counter = 0;
        struct dirent *entry;
        while (1)
        {
                entry = readdir(dp);
                if (entry != NULL && errno != 0)
                {
                        perror("mdrm: unable to remove directory");
                        exit(errno);
                }
                if (entry == NULL && errno == 0)
                {
                        break;
                }
                else
                {
                        if (entry->d_name[0] == '.')
                                continue;
                        counter++;
                }
        }
        return counter;
}
int isRegFile(char *source)
{
        struct stat fs;
        int rv = stat(source, &fs);
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
int isDir(char *source)
{
        struct stat fs;
        int rv = stat(source, &fs);
        if (rv == 0)
        {
                int t_mode = fs.st_mode;
                if (S_ISDIR(t_mode))
                        return 0;
                return -1;
        }
        else
        {
                perror("stat");
                exit(rv);
        }
}
char myPath[1024];
/*
void doMove(char *filepath)
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
                }
                else
                {
                        snprintf(myPath, sizeof(myPath), "%s/%s", filepath, entry->d_name);
                        copyDirContent(myPath); // on directory/ies content
                }
        }
        closedir(dir);    
}
int copyDirContent(char *filepath)
{
        struct stat mystat;
        char buff[MAX_CHARS];
        int rv = stat(filepath, &mystat);
        int mode_t = mystat.st_mode;

        const char * binName = ".mdrm_temp/";

        int fdf = open(filepath, O_RDONLY);
        char *newFilePath = concat(binName, filepath);
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
int makeDirectory(char *dirpath)
{
        const char *binName = ".mdrm_temp/";
        const char *newPath = concat(binName,dirpath);
        struct stat st = {0};
        int rv = 0;
        if (stat(newPath, &st) == -1)
        {
               rv = mkdir(newPath, 0700);
        }
        return rv;
}

static const char *concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
  //in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}
*/