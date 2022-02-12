/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:33:04 by hectfern          #+#    #+#             */
/*   Updated: 2022/02/11 16:01:43 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void send_signal(int process_id, int signal)
{
	kill(process_id, signal);
	usleep(9000);
}

static void char_to_bin(unsigned int n, pid_t process_id)
{
	int		i;
	int		k;
	i = 6;
	while (i >= 0)
	{
		k = n >> i;
		printf("k: %u | i: %u | ", k, i);
		printf("k & i : %u | ", k & 1);
		printf("\n");
		if ((k & 1) > 0)
			send_signal(process_id, SIGUSR2);
		else
			send_signal(process_id, SIGUSR1);
		i--;
	}
	return ;
}

static void	send_binaries(pid_t process_id, char *string_param)
{
	while (*string_param)
	{
		char_to_bin(*string_param, process_id);
		string_param++;
	}
	char_to_bin(*string_param, process_id);
}

static void handler_action_client(int sig_number)
{
	if(sig_number == SIGUSR2)
		return;
	printf("End communication");
	exit(0);
}

int	main(int argc, char *argv[])
{
	int		process_id;
	char	*string_param;
	struct sigaction	action;

	process_id = ft_atoi(argv[1]);
	if (argc != 3 || process_id <= 1)
	{
		printf("Invalid arguments, use: ./client <process_id> <string>\n");
		return (0);
	}
	action.sa_flags = SA_SIGINFO;
	action.sa_handler = handler_action_client;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	string_param = argv[2];
	send_binaries(process_id, string_param);
	return (0);
}