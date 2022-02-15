#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"

void bin(unsigned n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);
 
    /* step 2 */
    printf("%d", n % 2);
}

void char_bin(pid_t pid, char c)
{
	int count = 6;
	int x;
	// printf("%c: ", c);
	// bin(c);
	// printf("\n");
	while(count >= 0)
	{
		x = c >> count;
		if ((x & 1) > 0)
		{
			kill(pid, SIGUSR2);
			usleep(2042);
		}
		else
		{
			kill(pid, SIGUSR1);
			usleep(2042);
		}
		count --;
	}
}

void handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	(void)info;
	printf("End comunication\n");
}

void send_message(int pid, char *message)
{
	while(*message)
	{
		char_bin(pid, *message);
		message++;
	}
	char_bin(pid, *message);
}

int main(int argc, char *argv[])
{
	int pid;
	struct sigaction act;
	char *msg;

	if (argc != 3)
	{
		printf("Usage: %s <pid> [message]\n", argv[0]);
		return 1;
	}
	
	pid = atoi(argv[1]);
	msg = argv[2];
	send_message(pid, msg);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	
	return 0;
}
