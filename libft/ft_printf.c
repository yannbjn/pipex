/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:38:36 by yabejani          #+#    #+#             */
/*   Updated: 2024/01/18 16:23:16 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_type(char c, va_list args)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (c == 's')
		return (ft_print_s(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_p(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_di(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_print_xx(va_arg(args, int), 1));
	else if (c == 'X')
		return (ft_print_xx(va_arg(args, int), 42));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *form, ...)
{
	int		len;
	int		i;
	va_list	args;

	if (!form)
		return (-1);
	len = 0;
	i = 0;
	va_start(args, form);
	while (form[i])
	{
		if (form[i] == '%')
		{
			i++;
			len += print_type(form[i], args);
		}
		else
			len += write(1, &form[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
