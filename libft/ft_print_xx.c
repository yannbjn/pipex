/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:26:58 by yabejani          #+#    #+#             */
/*   Updated: 2024/01/18 16:23:16 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_len(unsigned int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

static void	rec_print_hex(unsigned int nbr, int flag)
{
	static char	lowcase[16] = "0123456789abcdef";
	static char	uppcase[16] = "0123456789ABCDEF";

	if (nbr >= 16)
		rec_print_hex((nbr / 16), flag);
	if (flag == 1)
		write(1, &lowcase[nbr % 16], 1);
	else if (flag == 42)
		write(1, &uppcase[nbr % 16], 1);
}

int	ft_print_xx(unsigned int nbr, int flag)
{
	rec_print_hex(nbr, flag);
	return (nbr_len(nbr));
}
