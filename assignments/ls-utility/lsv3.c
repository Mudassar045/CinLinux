#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
extern int errno;
void do_ls(char*);
int main(int argc, char**argv)
{
    // reading content of pwd/cwd directory
    if(argc==1)
    {
        do_ls(".");
    }
    else
    {
        // printing content of given directory
        int i = 0;
        while(++i<argc)
        {
            printf("Directory listing of %s:\n",argv[i]);
            do_ls(argv[i]);
        }
    }
    exit(0);
}
void do_ls(char* dir)
{
    DIR* dp = opendir(dir);
    //display file or file system status
    struct stat statFile;
    struct dirent* entry;
    errno = 0;
    if(dp==NULL)
    {
        fprintf(stderr, "Can't open directory: %s",dir);
        exit(errno);
    }
    while(1)
    {
        entry=readdir(dp);
        if(entry!=NULL && errno!=0)
        {
            perror("readdir failed");
            exit(errno);
        }
        if(entry==NULL && errno==0)
        {
          return;
        }
        else
        {
            //checck for hidden items
            if(entry->d_name[0]=='.')
              continue;
            int rv = stat(entry->d_name, &statFile);
            if (rv)
            {
              perror ("stat");
              exit(rv);
            }
            printf("%ld   %s\n",statFile.st_size,entry->d_name);
        }
    }
    closedir(dp);
}
int isDirectory(char* dir)
{
     DIR* dp = opendir(dir);
     if(dp==NULL)
     {
         return 0;
     }
     else
     {
         return 1;
     }
}
int isDirectoryHasContent(char* dir)
{
    DIR* dp = opendir(dir);
    errno = 0;
    struct dirent* entry;
    entry = readdir(dp);
    if(entry==NULL && entry==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
/*
int isOption(char* opt)
{
    opt=="-l"? return 1:return false;
    opt=="-R"? return 1:return false;
    opt=="-a"? return 1:return false;
    opt=="-n"? return 1:return false;
}
*/
