#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char FileType(int);
void longlisting(char* entry,struct stat statF);
void printPermissions(int);
void do_ls(char*);
int compareStrings(const void *A, const void *B);
int DirectoryEntries(char*);
extern int errno;
int main(int argc, char**argv)
{
    if(argc==1)
    {
        do_ls(".");
    }
    else
    {
        int i = 0;
        while(++i<argc)
        {
            printf("Directory contents of %s:\n",argv[i]);
            do_ls(argv[i]);
        }
    }
    exit(0);
}
void do_ls(char* dir)
{
    int des = DirectoryEntries(dir);
    char ** DirArray = (char**)malloc(sizeof(char*)*des);
    DIR* dp = opendir(dir);
    struct stat statF;
    struct dirent* entry;
    int returnvalue = 0;
    errno = 0;
    int i = 0;
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
            perror("readdir");
            exit(errno);
        }
        if(entry==NULL && errno==0)
        {
          break;
        }
        else
        {
            if(entry->d_name[0]=='.')
              continue;
            DirArray[i] = malloc(sizeof(char*)*(strlen(entry->d_name)+1));
            strcpy(DirArray[i++],entry->d_name);
        }
    }
    qsort (DirArray, des, sizeof ( *DirArray),
       compareStrings );
    for(int i = 0; i<des;i++)
    {
      returnvalue = stat(DirArray[i], &statF);
      if (returnvalue)
      {
        fprintf(stderr, "stat");
        exit(returnvalue);
      }
      longlisting(DirArray[i], statF);
    }
}

void printPermissions(int mode)
{
  printf("%c",FileType(mode));
  // file owener permsissions
  printf("%c",(mode & 00400) ? 'r' : '-');
  printf("%c",(mode & 00200) ? 'w' : '-');
  printf("%c",(mode & 00100) ? 'x' : '-');
  // group permissions
  printf("%c",(mode & 00040) ? '-' : 'r');
  printf("%c",(mode & 00020) ? 'w' : '-');
  printf("%c",(mode & 00010) ? 'x' : '-');
  // others permissions
  printf("%c",(mode & 00004) ? '-' : 'r');
  printf("%c",(mode & 00002) ? 'w' : '-');
  printf("%c",(mode & 00001) ? 'x' : '-');
}
void longlisting(char *d, struct stat statF)
{
  char date[20];
  struct group  *gr = getgrgid(statF.st_gid);
  struct passwd *wn = getpwuid(statF.st_uid);
  if(gr==NULL && gr==0)
  {
    return;
  }
  if(wn==NULL && wn==0)
  {
    return;
  }
  strftime(date, sizeof(date), "%b  %d %H:%M", localtime(&(statF.st_ctime)));
  printf("%2ld ",statF.st_blocks);printPermissions(statF.st_mode);
  printf(" %ld %s %s %6ld %s %s\n",statF.st_nlink,wn->pw_name,
  gr->gr_name,statF.st_size,date,d);
}
char FileType(int st_mode)
{
   if(S_ISDIR(st_mode))
   {
     return 'd';
   }
   else if(S_ISSOCK(st_mode))
   {
     return 's';
   }
   else if(S_ISFIFO(st_mode))
   {
     return 'p';
   }
    else if(S_ISREG(st_mode))
   {
     return '-';
   }
   else if(S_ISLNK(st_mode))
   {
     return 'l';
   }
   else if(S_ISCHR(st_mode))
   {
     return 'c';
   }
   else if(S_ISBLK(st_mode))
   {
     return 'b';
   }
   else
   {
     return 'u';
   }
}
int DirectoryEntries(char* d)
{
  DIR* dp = opendir(d);
  errno = 0;
  int dc = 0;
  struct dirent* entry;
  while(1)
  {
    entry = readdir(dp);
    if(entry!=NULL && errno!=0)
    {
        perror("readdir");
        exit(errno);
    }
    if(entry==NULL && errno==0)
    {
      return dc;
    }
    else
    {
      if(entry->d_name[0]=='.')
        continue;
        dc++;
    }
  }
}
int compareStrings(const void *A, const void *B)
{
  const char *p1=*(const char**)A;
  const char *p2=*(const char**)B;
  return strcmp(p1,p2);
}
