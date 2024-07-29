/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:06:57 by manufern          #+#    #+#             */
/*   Updated: 2024/07/12 14:29:32 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk_bonus.h"

static pid_t	g_pid_client;

void	ft_write(char *str, int num_malloc)
{
	write(1, str, num_malloc);
	write(1, "\n", 1);
	free(str);
}

int	handle_message(int *i, int *signum, int num_malloc)
{
	static char	*c = NULL;
	static int	letter_counter = 0;

	if (*i == 32)
	{
		c = malloc(num_malloc + 1);
		if (!c)
			exit(EXIT_FAILURE);
		ft_memset(c, 0, num_malloc + 1);
	}
	c[letter_counter] |= (*signum == SIGUSR1) << (7 - (*i % 8));
	if (*i % 8 == 7)
	{
		letter_counter++;
		if (letter_counter == num_malloc)
		{
			ft_write(c, num_malloc);
			letter_counter = 0;
			c = NULL;
			kill(g_pid_client, SIGUSR1);
			return (1);
		}
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	num_malloc = 0;

	(void)context;
	if (info->si_pid != 0)
		g_pid_client = info->si_pid;
	if (i < 32)
		num_malloc |= (signum == SIGUSR1) << (31 - i);
	else
	{
		if (handle_message(&i, &signum, num_malloc) == 1)
		{
			i = 0;
			num_malloc = 0;
			return ;
		}
	}
	i++;
	kill(g_pid_client, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	ft_printf("PID del servidor: %d\n", getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
