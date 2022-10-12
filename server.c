/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuomitsuru <matsuomitsuru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:18:35 by mmatsuo           #+#    #+#             */
/*   Updated: 2022/10/12 18:26:04 by matsuomitsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_signal	g_signal;

void	put_character(int signal)
{
	if (signal == SIGUSR1)
		g_signal.character = g_signal.character * 2 + 1;
	else
		g_signal.character = g_signal.character * 2 + 0;
	if (g_signal.count == 7)
	{
		ft_putchar_fd(g_signal.character, STDOUT_FILENO);
		g_signal.character = 0;
		g_signal.count = 0;
		return ;
	}
	g_signal.count++;
}

int	main(void)
{
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_signal.character = 0;
	g_signal.count = 0;
	signal(SIGUSR1, put_character);
	signal(SIGUSR2, put_character);
	while (1)
		pause();
}
