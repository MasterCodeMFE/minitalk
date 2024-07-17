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

// Variable global para indicar si se recibió la confirmación del servidor
volatile sig_atomic_t confirmacion_recibida = 0;

// Manejador de señal para SIGUSR1
void sigusr1_handler(int signum)
{
	(void)signum;
	confirmacion_recibida = 1;
}

// Función para enviar señales correspondientes a los bits del mensaje
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
		
		usleep(1000); // Esperar un poco entre cada señal
		while (!confirmacion_recibida)
			pause(); // Esperar por la señal de confirmación del servidor
		
		confirmacion_recibida = 0; // Reiniciar la bandera
		bit--;
	}
}

// Función para enviar el mensaje como señales de bits
void send_signals(pid_t pid, char *mensaje)
{
	char c;
	int i, j, bit;

	i = 0;
	j = 0;
	while (mensaje[i] != '\0')
		i++;
	send_str_ms(i, pid);
	while (j < i)
	{
		c = mensaje[j];
		bit = 7;
		while (bit >= 0)
		{
			if (c & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			
			usleep(1000); // Esperar un poco entre cada señal
			while (!confirmacion_recibida)
				pause(); // Esperar por la señal de confirmación del servidor
			
			confirmacion_recibida = 0; // Reiniciar la bandera
			bit--;
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

	// Establecer el manejador de señales para SIGUSR1
	struct sigaction sa;
	sa.sa_handler = sigusr1_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);

	// Llamar a la función para enviar el mensaje
	send_signals(pid, mensaje);

	return 0;
}
