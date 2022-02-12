/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:33:15 by hectfern          #+#    #+#             */
/*   Updated: 2022/02/11 15:13:22 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bit_to_char(int bit, pid_t client_pid)
{
	static int	holder = 0;
	static int	g_counter = 6;

	holder += bit << g_counter;
	g_counter--;
	if (g_counter < 0)
	{
		if (holder == '\0')
		{
			printf("\n");
			kill(client_pid, SIGUSR1);
		}
		printf("%c", holder);
		holder = 0;
		g_counter = 6;
	}
	kill(client_pid, SIGUSR2);
}

static void	handler_action(int sig_number, siginfo_t *act_info, void *context)
{
	(void)context;
	if (!sig_number)
		return ;
	bit_to_char(sig_number == SIGUSR2, act_info->si_pid);
}

int	main(void)
{
	struct sigaction	action;

	printf("Server PID: %d\n", getpid());
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler_action;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
