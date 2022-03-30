#include <stdio.h>
#include <utmp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp*);
void showtime(long);
int utmp_open(char*);
struct utmp* utmp_next();
int utmp_reload();
void utmp_close();

int main()
{
	//struct utmp current_record;
	//int	utmpfd = -1;
	//int reclen = sizeof(current_record);

	//if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	//{
	//	perror(UTMP_FILE);
	//	exit(1);
	//}
	//while (read(utmpfd, &current_record, reclen) == reclen)
		//show_info(&current_record);
	struct utmp* utbufp;
	struct utmp* utmp_next();
	if (utmp_open(UTMP_FILE) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while ((utbufp = utmp_next()) != (struct utmp*)NULL)
		show_info(utbufp);
	utmp_close();
	//close(utmpfd);
	return 0;
}

void show_info(struct utmp* utmpfp)
{
	if (utmpfp->ut_type != USER_PROCESS)
		return ;
	printf("%-8.8s", utmpfp->ut_user);
	printf(" ");
	printf("%-8.8s", utmpfp->ut_line);
	printf(" ");
	showtime(utmpfp->ut_time);
	printf(" ");
#ifdef SHOWHOST
	if (utmpfp->ut_host[0] != '\0')
		printf("(%s)", utmpfp->ut_host);
#endif
	printf("\n");
}

void showtime(long timeval)
{
	char* cp = NULL;
	cp = ctime(&timeval);
	printf("%12.12s", cp+4);
}
