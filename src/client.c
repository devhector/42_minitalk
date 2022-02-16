/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:56:52 by hectfern          #+#    #+#             */
/*   Updated: 2022/02/16 11:55:49 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	g_signal_control;

static void	convert_bin(pid_t	pid, char c)
{
	int	x;
	int	count;

	count = 8;
	while (count >= 0)
	{
		x = c >> count;
		if ((x & 1) > 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		count --;
		while (!g_signal_control)
			pause();
		g_signal_control = 0;
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
		g_signal_control = 1;
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
	g_signal_control = 0;
	send_message(atoi(argv[1]), argv[2]);
	return (0);
}
