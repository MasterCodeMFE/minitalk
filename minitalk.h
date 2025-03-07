/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:12:03 by manufern          #+#    #+#             */
/*   Updated: 2024/07/03 13:12:01 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <string.h>
# include <strings.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>

int		ft_printf(char const *str, ...);
void	ft_flag(va_list args, char c, int *len);
int		ft_is_format(char c);
void	ft_putstr(char *str, int *len);
void	ft_hexa(unsigned long long nb, char *base, int *len);
void	ft_unsing(int nbr, char *base, int *len);
void	ft_putnbr_base(int nbr, char *base, int *len);
int		check_base(char *base);
void	ft_putchar(char c, int fd, int *len);
void	*ft_memset(void *b, int c, size_t len);
#endif
