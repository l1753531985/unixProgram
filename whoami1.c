#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define NAMESIZE 256

int main(int argc, char* argv[])
{
	printf("%-8.8s\n", getlogin());
	return 0;
}
