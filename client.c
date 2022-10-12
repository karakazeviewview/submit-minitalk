/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuomitsuru <matsuomitsuru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:18:35 by mmatsuo           #+#    #+#             */
/*   Updated: 2022/10/12 18:59:21 by matsuomitsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_msg(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	send_msg(int pid, char *msg)
{
	int		kill_status;
	int		i;
	int		shift_count;

	i = 0;
	while (msg[i] != '\0')
	{
		shift_count = 0;
		while (shift_count < 8)
		{
			// if ((msg[i] >> (7 - shift_count)) & 0b00000001)
			if ((msg[i] >> (7 - shift_count)) & 1)
				kill_status = kill(pid, SIGUSR1);
			else
				kill_status = kill(pid, SIGUSR2);
			if (kill_status == -1)
				error_msg("kill error");
			shift_count++;
			usleep(10000);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		error_msg("invalid argument\n");
	if (ft_strlen(argv[1]) > 7)
		error_msg("too long pid");
	pid = ft_atoi(argv[1]);
	send_msg(pid, argv[2]);
	return (0);
}
