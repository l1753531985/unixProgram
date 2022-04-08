#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void do_ls(char dirname[])
{
	DIR* dirfd = NULL;
	struct dirent* direntp = NULL;

	if ((dirfd = opendir(dirname)) == NULL)
	{
		printf("Error: Cannot open %s\n", dirname);
		exit(1);
	}

	while ((direntp = readdir(dirfd)) != NULL)
	{
		printf("%s\n", direntp->d_name);
	}

	if (closedir(dirfd) == -1)
	{
		printf("Error: Cannot close %s\n", dirname);
		exit(1);
	}
}

int main(int ac, char* av[])
{
	if (ac == 1)
		do_ls(".");
	else 
		while (--ac)
		{
			printf("%s:\n", *++av);
			do_ls(*av);
		}
	return 0;
}
