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

#include "./../minitalk.h"


/* int	ft_atoi(const char *str)
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
		i ++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i ++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i ++;
	}
	return (num * sig);
}

void send_str_ms (int long_ms, pid_t pid)
{
	int bit;

	bit = 0;
	while (bit < 32)
	{
		if (long_ms & (1 << bit))
		{
			ft_printf("1\n");
			kill(pid, SIGUSR1);
		}
		else
		{
			ft_printf("0\n");
			kill(pid, SIGUSR2);
		}
	usleep(5000);
	bit ++;
	}

}

void send_signals(pid_t pid, char *mensaje)
{
	char c;
	int i, j, bit;

	i = 0;
	j = 0;
	while (mensaje[i] != '\0')
		i++;
	send_str_ms(i, pid);
while (j <= i)
	{
		c = mensaje[j]; //H = 0100 1000
		bit = 0;
		ft_printf("letra: %c\n",c);
		while (bit < 8)
		{
			if (c & (1 << bit))
			{
				ft_printf("1\n");
				kill(pid, SIGUSR1);
			}
			else
			{
				ft_printf("0\n");
				kill(pid, SIGUSR2);
			}
			usleep(5000); // Pequeña pausa entre señales
			bit++;
		}
		usleep(5000); // Pausa adicional entre caracteres
		j++;
	}
	// Enviar señal de finalización al servidor
}

int main(int argc, char *argv[])
{
	pid_t pid;
	
	if (argc != 3)
	{
		printf("Uso: %s <PID_servidor> <mensaje>\n", argv[0]);
		exit(1);
	}

	pid = ft_atoi(argv[1]);
	char *mensaje = argv[2];
	
	// Enviar señales al proceso servidor
	send_signals(pid, mensaje);
	return 0;
} */

int ft_atoi(const char *str)
{
	int i;
	int num;
	int sig;

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

void send_str_ms(int long_ms, pid_t pid)
{
	int bit;

	bit = 31;
	while (bit >= 0)
	{
		if (long_ms & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit--;
	}
}

void send_signals(pid_t pid, char *mensaje)
{
	char    c;
	int     i;
	int     j;
	int     bit;

	i = 0;
	j = 0;
	while (mensaje[i] != '\0')
		i++;
	send_str_ms(i, pid);
	while (j < i)
	{
		c = mensaje[j];
		bit = 8;
		while (--bit >= 0)
		{
			if (c & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(400);
		}
		j++;
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;

	if (argc != 3)
	{
		printf("Uso: %s <PID_servidor> <mensaje>\n", argv[0]);
		exit(1);
	}

	pid = ft_atoi(argv[1]);
	char *mensaje = argv[2];

	// Enviar señales al proceso servidor
	send_signals(pid, mensaje);
	return 0;
}