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

#include "./../minitalk.h"
static pid_t pid_client;
void signal_handler(int signum, siginfo_t *info, void *context)
{
	static int letter_counter = 0;
	static int i = 0;
	static char *c = NULL;
	static int num_malloc = 0;

	(void)context;
	if (info->si_pid != 0)
		pid_client = info->si_pid;
	
	if (i < 32) // Primero recibimos el tamaño del mensaje
	{
		num_malloc |= (signum == SIGUSR1) << (31 - i);
	}
	else
	{
		if (i == 32) // Inicialización para el primer carácter
		{
			c = malloc(num_malloc + 1);
			if (!c)
				exit(EXIT_FAILURE);
			memset(c, 0, num_malloc + 1);
		}
		c[letter_counter] |= (signum == SIGUSR1) << (7 - (i % 8));
		if (i % 8 == 7) // Hemos recibido 8 bits, incrementamos el contador de letras
		{
			letter_counter++;
			if (letter_counter == num_malloc) // Si hemos recibido todo el mensaje
			{
				write(1, c, num_malloc);
				write(1, "\n", 1);
				free(c); // Liberar la memoria asignada a c
				c = NULL; // Restablecer c a NULL
				letter_counter = 0; // Restablecer el contador de letras
				i = 0; // Restablecer el índice de bits
				num_malloc = 0;
				kill(pid_client, SIGUSR1); // Restablecer el tamaño del mensaje
				return;
			}
			// Enviar señal de confirmación al cliente después de cada byte recibido
		}
	}
	i++;
	kill(pid_client, SIGUSR1);
}

int main(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	printf("PID del servidor: %d\n", getpid());

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO; // Indicar que estamos utilizando sa_sigaction
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
	{
		pause(); // Esperar por señales
	}

	return 0;
}
