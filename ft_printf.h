/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:45:56 by manufern          #+#    #+#             */
/*   Updated: 2023/11/27 18:56:26 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <strings.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(char const *str, ...);
void	ft_flag(va_list args, char c, int *len);
int		ft_is_format(char c);
void	ft_putstr(char *str, int *len);
void	ft_hexa(unsigned long long nb, char *base, int *len);
void	ft_unsing(int nbr, char *base, int *len);
void	ft_putnbr_base(int nbr, char *base, int *len);
int		check_base(char *base);
void	ft_putchar(char c, int fd, int *len);
#endif
