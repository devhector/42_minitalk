#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void bin(unsigned n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);
 
    /* step 2 */
    printf("%d", n % 2);
}

void bit(int bit, pid_t client)
{
	static int counter = 6;
	static int character = 0;
	char c;

	// printf("Entrou no bit - ");
	// printf("count: %d\n", counter);
	character += (bit << counter);
	counter--;
	if (counter < 0)
	{
		// printf("%c :", character);
		// bin(character);
		// printf("\n");
		if(character == '\0')
		{
			character = '\n';
			kill(client, SIGUSR1);
		}
		counter = 6;
		c = character;
		write(1, &c, 1);
		character = 0;
	}
}

static void handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	// printf("Entrou handler\n");
	bit(SIGUSR2 == sig, info->si_pid);
}

int main()
{
	struct sigaction act;

	printf("PID: %d\n", getpid());
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	while (1) {
		pause();
	}
	return 0;
}