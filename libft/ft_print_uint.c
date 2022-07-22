/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:09:04 by mraspors          #+#    #+#             */
/*   Updated: 2022/03/20 18:48:24 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uint(unsigned int nbr)
{
	char	c;
	int		length;

	length = 0;
	if (nbr == 4294967295)
	{
		write(1, "4294967295", 10);
		return (10);
	}
	if (nbr >= 10)
		length += ft_print_uint(nbr / 10);
	c = (nbr % 10) + '0';
	length += ft_print_char(c);
	return (length);
}
