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

void signal_handler(int signum)
{
    static int letter_counter = 0;
    static int i = 0;
    static char *c = NULL;
    static int num_malloc = 0;

    if (i < 32) // Primero recibimos el tamaño del mensaje
    {
        num_malloc |= (signum == SIGUSR1) << (31 - i);
    }
    else
    {
        if (i == 32) // Inicialización para el primer carácter
        {
            c = malloc(num_malloc + 1); // Asegurarse de tener espacio para el carácter nulo
            if (!c)
                exit(EXIT_FAILURE);
            memset(c, 0, num_malloc + 1); // Inicializar la memoria con 0
        }
        c[letter_counter] |= (signum == SIGUSR1) << (7 - (i % 8));
        if (i % 8 == 7) // Hemos recibido 8 bits, incrementamos el contador de letras
        {
            letter_counter++;
            if (letter_counter == num_malloc) // Si hemos recibido todo el mensaje
            {
                write(1, c, num_malloc);
                write(1, "\n", 1); // Escribir el mensaje
                free(c); // Liberar la memoria asignada a c
                c = NULL; // Restablecer c a NULL
                letter_counter = 0; // Restablecer el contador de letras
                i = 0; // Restablecer el índice de bits
                num_malloc = 0; // Restablecer el tamaño del mensaje
                return;
            }
        }
    }
    i++;
}

int main(void)
{
    struct sigaction sa;

    printf("PID del servidor: %d\n", getpid());

    sa.sa_handler = &signal_handler;
    sa.sa_flags = SA_RESTART; // Asegurar que las llamadas al sistema interrumpidas se reinicien
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
    {
        pause(); // Esperar por señales
    }

    return 0;
}
