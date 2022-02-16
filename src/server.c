/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:57:28 by hectfern          #+#    #+#             */
/*   Updated: 2022/02/16 15:42:42 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	convert_bit(int bit, int *finish)
{
	static int	counter = 10;
	static int	character = 0;

	character += (bit << counter);
	counter--;
	if (counter < 0)
	{
		if (character == '\0')
		{
			character = '\n';
			*finish = 1;
		}
		counter = 10;
		write(1, &character, 1);
		character = 0;
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	int	finish;

	finish = 0;
	if (!sig)
		return ;
	convert_bit(SIGUSR2 == sig, &finish);
	kill(info->si_pid, SIGUSR1);
	if (finish)
		kill(info->si_pid, SIGUSR2);
	(void)context;
}

int	main(void )
{
	struct sigaction	act;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (42)
	{
		pause();
	}
	return (0);
}
