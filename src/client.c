/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:56:52 by hectfern          #+#    #+#             */
/*   Updated: 2022/02/17 20:28:38 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	g_signal_control;

static void	send_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Connection not established\n", 1);
		exit(1);
	}
}

static void	convert_bin(pid_t	pid, char c)
{
	int	x;
	int	count;

	count = 10;
	while (count >= 0)
	{
		x = c >> count;
		if ((x & 1) == 1)
			send_signal(pid, SIGUSR2);
		else
			send_signal(pid, SIGUSR1);
		count --;
		while (g_signal_control)
			pause();
		g_signal_control = 1;
	}
}

static void	send_message(int pid, char *message)
{
	while (*message)
	{
		convert_bin(pid, *message);
		message++;
	}
	convert_bin(pid, *message);
}

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_signal_control = 0;
	else if (sig == SIGUSR2)
		ft_putstr_fd("Message sent!\n", 1);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	act.sa_handler = handler;
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> [message]\n", 1);
		return (1);
	}
	g_signal_control = 1;
	send_message(atoi(argv[1]), argv[2]);
	return (0);
}
