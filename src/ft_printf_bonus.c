/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:52:33 by manufern          #+#    #+#             */
/*   Updated: 2024/07/12 11:45:32 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "./../minitalk_bonus.h"

void	ft_hexa(unsigned long long nb, char *base, int *len)
{
	if (nb == 0)
	{
		ft_putchar(base[0], 1, len);
		return ;
	}
	if (nb >= 16)
	{
		ft_hexa(nb / 16, base, len);
		ft_hexa(nb % 16, base, len);
	}
	else
		ft_putchar(base[nb], 1, len);
	if (*len == -1)
		return ;
}

void	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
	{
		i = write(1, "(null)", 6);
		if (i == -1)
		{
			*len = -1;
			return ;
		}
		(*len) += 6;
		return ;
	}
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar (str[i], 1, len);
		if (*len == -1)
			return ;
		i ++;
	}
}

int	ft_is_format(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

void	ft_flag(va_list args, char c, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), 1, len);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (c == 'p')
	{
		if (write(1, "0x", 2) == -1)
		{
			*len = -1;
			return ;
		}
		(*len) += 2;
		ft_hexa(va_arg(args, unsigned long long), "0123456789abcdef", len);
	}
	else if (c == 'd' || c == 'i')
		ft_putnbr_base(va_arg(args, int), "0123456789", len);
	else if (c == 'u')
		ft_unsing(va_arg(args, unsigned int), "0123456789", len);
	else if (c == 'x')
		ft_unsing(va_arg(args, unsigned int), "0123456789abcdef", len);
	else if (c == 'X')
		ft_unsing(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	else if (c == '%')
		ft_putchar('%', 1, len);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_is_format(str[i + 1]))
		{
			ft_flag(args, str[i + 1], &len);
			i++;
		}
		else if (str[i] != '%')
			ft_putchar(str[i], 1, &len);
		if (len == -1)
			return (len);
		i++;
	}
	va_end(args);
	return (len);
}
