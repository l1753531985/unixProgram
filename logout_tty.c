#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>	

int utmp_open(char*);
struct utmp* utmp_next();
int utmp_close();
int utmp_seek(off_t, int);
int utmp_write(const void*, size_t);

void set_dead(struct utmp* utbufp)
{
	int len = sizeof(struct utmp);
	utbufp->ut_type = DEAD_PROCESS;
	if (utmp_seek(-len,SEEK_CUR) != -1)
		if (utmp_write(utbufp, len) == len)
			printf("set dead successfully");
}

void logout_tty(char* line)
{
	struct utmp* utbufp;
	utmp_open(UTMP_FILE);
	while ((utbufp = utmp_next()) != (struct utmp*)NULL)
		if (strncmp(utbufp->ut_line, line, sizeof(utbufp->ut_line)) == 0)
			set_dead(utbufp);
	utmp_close();
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		perror("Error: No any tty name to logout");
		exit(1);
	}
	logout_tty(argv[1]);
	return 0;
}

