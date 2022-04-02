#include <stdio.h>
#include <utmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>	

int utmp_open(char*);
struct utmp* utmp_next();
int utmp_close();

void set_dead(struct utmp* utbufp)
{
	utbufp->ut_type = DEAD_PROCESS;
}

void logout_tty(char* line)
{
	struct utmp* utbufp;
	utmp_open(UTMP_FILE);
	while ((utbufp = utmp_next()) != (struct utmp*)NULL)
		if (strncmp(utbufp->ut_line, line, sizeof(ut_line)))
			set_dead(utbufp);
	utmp_close();
}

int main(int argc, char* argv[])
{
	logout_tty(argv[1]);
}

