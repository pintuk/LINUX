#include<sys/types.h>
#include<sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include<string.h>

#include<stdlib.h>


#define MAX_COUNT	3




int RemoveDirectory(char *dirpath, char *dirstartname)
{
        struct dirent *d = NULL;		
        DIR *dir = NULL;
        char buf[256] = {0};
		char vtdir[256] = {0};
		char firstdir[256] = {0};
		int count = 0;
		static int firsttime = 1;
		struct stat s;
		long int createtime = 0;
		long int mintime = 0;
		

        dir = opendir(dirpath);
		if(dir == NULL)
		{
			perror("ERROR : opendir : ");
			exit(0);
		}

        while(d = readdir(dir))
        {
				//static int firsttime = 1;
				
				if(strstr(d->d_name,dirstartname))
				{
                	printf("%s\n",d->d_name);
					//if(firsttime == 1)
					{
						//strcpy(firstdir,d->d_name);
						sprintf(vtdir, "%s/%s", dirpath, d->d_name);
						stat(vtdir,&s);
						createtime = (long int)s.st_ctime;
						if(firsttime == 1)
						{
							mintime = createtime;
							firsttime = 0;
						}
						printf("Time = %ld\n",createtime);
						if(createtime < mintime) 
						{
							mintime = createtime;
							sprintf(firstdir, "%s/%s", dirpath, d->d_name);
						}
						firsttime = 0;
					}
					count++;
				}
        }
		printf("MAX Count = %d\n",count);
		printf("Oldest vtdir == %s\n",firstdir);
		exit(0);


		if(count == MAX_COUNT)
		{
			struct dirent *d1;
			DIR *dir1;

			dir1 = opendir(firstdir);
			while(d1 = readdir(dir1))
			{
				printf("File --> %s\n",d1->d_name);
				if((strcmp(d1->d_name,".")!=0) && (strcmp(d1->d_name,"..")!=0))
				{
					sprintf(buf, "%s/%s", firstdir,d1->d_name);
					printf("buf = %s\n",buf);
					remove(buf);
				}
			}
			closedir(dir1);
			remove(firstdir);
			printf("First Dir Removed -- %s\n",firstdir);
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


