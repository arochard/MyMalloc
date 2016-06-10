/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:36:36 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:36:39 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				ft_putchar(char c)
{
	write(1, &c, 1);
}

void				ft_putstr(char const *s)
{
	while (*s != '\0')
	{
		ft_putchar(*s);
		s++;
	}
}

void				*ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

void				ft_puthexa(size_t dec)
{
	size_t			i;

	if (dec)
	{
		i = dec / 16;
		ft_puthexa(i);
		if (dec % 16 < 10)
			ft_putchar('0' + dec % 16);
		else
			ft_putchar('a' + (dec % 16) - 10);
	}
	else
		ft_putstr("0x");
	return ;
}

void				ft_putnbr(int nb)
{
	if (nb > 2147483647)
		return ;
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar('-');
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48);
		return ;
	}
	ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + 48);
	return ;
}
