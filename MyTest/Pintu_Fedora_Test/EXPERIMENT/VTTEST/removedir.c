#include<sys/types.h>
#include<sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include<string.h>

#include<stdlib.h>


#define MAX_COUNT	3


int CountDir(DIR *vtdir, char *startname)
{
	int count = 0;
	struct dirent *d = NULL;

	if(vtdir == NULL) return 0;
	
	while(d = readdir(vtdir))
	{
		if(strstr(d->d_name, startname))
		{
			count++;
		}
	}
	return(count);
}

int FindOldestDirectory(DIR *dir, char *dirpath, char *startname, char *oldestdir)
{

	struct stat s;
	struct dirent *d = NULL;
	char vtdir[256] = {0};
	long int created_time = 0;
	long int oldesttime = 0;
	int firsttime = 1;
	int retVal = 0;
	
	if(dir == NULL)
	{
		printf("FindOldestDirectory - dir is NULL\n");
		return 0;
	}

	printf("FindOldestDirectory -------->\n");

	while(d = readdir(dir))
	{
		if(strstr(d->d_name, startname))
		{		
			sprintf(vtdir, "%s/%s", dirpath, d->d_name);
			stat(vtdir,&s);
			created_time = (long int)s.st_ctime;
			if(firsttime == 1)
			{
				oldesttime = created_time;
				sprintf(oldestdir, "%s/%s", dirpath, d->d_name);
				retVal = 1;
				firsttime = 0;
			}
			printf("%s , Time = %ld\n",d->d_name,created_time);
			if(created_time < oldesttime)
			{
				oldesttime = created_time;
				sprintf(oldestdir, "%s/%s", dirpath, d->d_name);
				retVal = 1;
			}
		}
	}
	return(retVal);
}

int MakeDirEmpty(char *dirname)
{

	struct dirent *d = NULL;
	DIR *dir = NULL;
	char buf[256] = {0};
	char retval = 0;

	if(dirname == NULL) 
	{
		printf("MakeDirEmpty - dirname is NULL\n");
		return 0;
	}

	dir = opendir(dirname);
	while(d = readdir(dir))
	{
		if((strcmp(d->d_name,".")!=0) && (strcmp(d->d_name,"..")!=0))
		{
			sprintf(buf, "%s/%s", dirname,d->d_name);
			printf("File --> %s\n",buf);
			remove(buf);
			retval = 1;
		}
	}
	closedir(dir);
	return 1;
}


int RemoveDirectory(char *dirpath, char *dirstartname)
{
        struct dirent *d = NULL;
		DIR *Odir = NULL;
        DIR *dir = NULL;
		int numdirs = 0;
		char oldestDir[256] = {0};

        dir = opendir(dirpath);
		if(dir == NULL)
		{
			perror("ERROR : opendir : ");
			exit(0);
		}
		Odir = dir;

		printf("Directory path = %s\n",dirpath);

		numdirs = CountDir(dir, dirstartname);
		printf("Total Dir Count = %d\n",numdirs);

		//for(i=0; i<numdirs; i++)
		while(numdirs > MAX_COUNT)
		{
			rewinddir(Odir);
			memset(oldestDir, 0, sizeof(oldestDir));
			printf("--------------------------------------------------------------\n");
			if(FindOldestDirectory(Odir, dirpath, dirstartname, oldestDir) != 0)
			{
				printf("Oldest vtdir == %s\n",oldestDir);
				if(MakeDirEmpty(oldestDir) != 0)
				{
					//Directory is Empty - we can do rmdir
					if(remove(oldestDir) == 0)
					{
						printf("Directory Removed Successfully --- %s\n",oldestDir);
						numdirs--;
					}
					else
					{
						perror("ERROR : remove : ");
						break;
					}
				}
				else
				{
					printf("MakeDirEmpty - Failed - %s\n",oldestDir);
					break;
				}
			}
			else
			{
				printf("FindOldestDirectory - Not Found - %s\n",oldestDir);
				break;
			}
			printf("--------------------------------------------------------------\n");
			
		}
		closedir(dir);
        return 0;

}



main()
{
	char dirpath[] = "./vtdir";
	char startname[] = "vtlog-";

	RemoveDirectory(dirpath,startname);
}


