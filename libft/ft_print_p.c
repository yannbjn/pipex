/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:45:32 by yabejani          #+#    #+#             */
/*   Updated: 2024/01/18 16:23:16 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ptr_len(unsigned long long nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

static void	rec_print_ptr(unsigned long long ptr)
{
	static char	hex[] = "0123456789abcdef";

	if (ptr >= 16)
		rec_print_ptr(ptr / 16);
	write(1, &hex[ptr % 16], 1);
}

int	ft_print_p(void *ptr)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	rec_print_ptr((unsigned long long)ptr);
	return (ptr_len((unsigned long long)ptr) + 2);
}
