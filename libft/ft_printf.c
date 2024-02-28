/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:26:59 by cogata            #+#    #+#             */
/*   Updated: 2023/09/04 11:27:00 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	count = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			find_format(&args, format, &i, &count);
		}
		else
			count += ft_put_and_count_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_put_and_count_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_and_count_str(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			count += write(1, &s[i], 1);
			i++;
		}
	}
	else
		count += ft_put_and_count_str("(null)");
	return (count);
}

void	find_format(va_list *args, const char *format, int *i, int *count)
{
	if (format[*i] == 'c')
		*count += ft_put_and_count_char(va_arg(*args, int));
	else if (format[*i] == 's')
		*count += ft_put_and_count_str(va_arg(*args, char *));
	else if (format[*i] == 'p')
		*count += ft_base10_to_base16(va_arg(*args, unsigned long int),
				format[*i]);
	else if (format[*i] == 'd' || format[*i] == 'i')
		*count += ft_put_and_count_nbr(va_arg(*args, int));
	else if (format[*i] == 'u')
		*count += ft_unsigned_putnbr(va_arg(*args, unsigned int));
	else if (format[*i] == 'x' || format[*i] == 'X')
		*count += ft_base10_to_base16(va_arg(*args, unsigned int), format[*i]);
	else if (format[*i] == '%')
		*count += ft_put_and_count_char('%');
	else
	{
		*i -= 1;
		*count += ft_put_and_count_char(format[*i]);
		*i += 1;
	}
}
