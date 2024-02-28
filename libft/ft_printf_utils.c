/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:04:30 by cogata            #+#    #+#             */
/*   Updated: 2023/09/06 16:04:36 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_to_char(int nb)
{
	char	c;
	int		count;

	count = 0;
	if (nb > 9)
	{
		count += ft_int_to_char(nb / 10);
		c = (nb % 10) + '0';
		count += write(1, &c, 1);
	}
	else
	{
		c = nb + '0';
		count += write(1, &c, 1);
	}
	return (count);
}

int	ft_put_and_count_nbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	else if (nb >= 0 && nb <= 2147483647)
	{
		count += ft_int_to_char(nb);
	}
	else if (nb < 0 && nb >= -2147483647)
	{
		count += write(1, "-", 1);
		nb = nb * (-1);
		count += ft_int_to_char(nb);
	}
	return (count);
}

int	ft_unsigned_putnbr(unsigned int nb)
{
	char	c;
	int		count;

	count = 0;
	if (nb > 9)
	{
		count += ft_unsigned_putnbr(nb / 10);
		c = (nb % 10) + '0';
		count += write(1, &c, 1);
	}
	else
	{
		c = nb + '0';
		count += write(1, &c, 1);
	}
	return (count);
}

int	ft_base10_to_base16(unsigned long int nb, char type)
{
	unsigned int	count_base;
	char			*base;
	int				count;

	base = "0123456789abcdef";
	if (type == 'X')
		base = "0123456789ABCDEF";
	count_base = 16;
	count = 0;
	if (nb == 0 && type == 'p')
		return (count += ft_put_and_count_str("(nil)"));
	if (nb >= count_base)
	{
		count += ft_base10_to_base16(nb / count_base, type);
		count += write(1, &base[nb % count_base], 1);
	}
	else
	{
		if (type == 'p')
			count += write(1, "0x", 2);
		count += write(1, &base[nb], 1);
	}
	return (count);
}
