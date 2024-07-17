/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:52:33 by manufern          #+#    #+#             */
/*   Updated: 2024/07/12 11:45:29 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk.h"

void	ft_putchar(char c, int fd, int *len)
{
	if (write(fd, &c, 1) == -1)
	{
		*len = -1;
	}
	else
		(*len)++;
}

int	check_base(char *base)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (base[i] == '\0')
		return (0);
	while (base[i] != '\0')
	{
		j = i;
		while (base[j] != '\0')
		{
			if (base[j] == '+' || base[j] == '-')
				return (0);
			j ++;
			if (base[j] == base[i])
				return (0);
		}
		i ++;
	}
	return (i);
}

void	ft_putnbr_base(int nbr, char *base, int *len)
{
	unsigned int	size;
	unsigned int	num;

	size = check_base (base);
	if (size <= 1)
		return ;
	if (nbr < 0)
	{
		ft_putchar ('-', 1, len);
		num = nbr * -1;
	}
	else
		num = nbr;
	if (*len == -1)
		return ;
	if (num >= size)
	{
		ft_putnbr_base (num / size, base, len);
		if (*len == -1)
			return ;
		ft_putchar (base[num % size], 1, len);
	}
	else
		ft_putchar (base[num % size], 1, len);
}

void	ft_unsing(int nbr, char *base, int *len)
{
	unsigned int	size;
	unsigned int	num;

	size = check_base (base);
	if (size <= 1)
		return ;
	num = nbr;
	if (num >= size)
	{
		ft_putnbr_base (num / size, base, len);
		if (*len == -1)
			return ;
		ft_putchar (base[num % size], 1, len);
	}
	else
		ft_putchar (base[num % size], 1, len);
	if (*len == -1)
		return ;
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i ++;
	}
	return (b);
}
