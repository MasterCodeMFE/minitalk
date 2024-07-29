/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:07:51 by manufern          #+#    #+#             */
/*   Updated: 2024/07/12 16:52:14 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk_bonus.h"

volatile sig_atomic_t	g_confirm = 0;

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sig;

	i = 0;
	num = 0;
	sig = 1;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sig);
}

void	sigusr1_handler(int signum)
{
	(void)signum;
	g_confirm = 1;
}

void	send_str_ms(int long_ms, pid_t pid)
{
	int	bit;

	bit = 31;
	while (bit >= 0)
	{
		if (long_ms & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		while (!g_confirm)
			pause();
		g_confirm = 0;
		bit--;
	}
}

void	send_signals(pid_t pid, char *mensaje, char c)
{
	int		i;
	int		j;
	int		bit;

	i = 0;
	j = -1;
	while (mensaje[i] != '\0')
		i++;
	send_str_ms(i, pid);
	while (++j < i)
	{
		c = mensaje[j];
		bit = 8;
		while (--bit >= 0)
		{
			if (c & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(1000);
			while (!g_confirm)
				pause();
			g_confirm = 0;
		}
	}
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
	char				*mensaje;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Uso: %s <PID_servidor> <mensaje>\n", argv[0]);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	mensaje = argv[2];
	sa.sa_handler = sigusr1_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	send_signals(pid, mensaje, 0);
	return (0);
}
