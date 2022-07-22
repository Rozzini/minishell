/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:08:55 by mraspors          #+#    #+#             */
/*   Updated: 2022/03/20 18:48:13 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_number(int nbr)
{
	char	c;
	int		length;

	length = 0;
	if (nbr == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (nbr < 0)
	{
		length += ft_print_char('-');
		nbr *= -1;
	}
	if (nbr >= 10)
		length += ft_print_number(nbr / 10);
	c = nbr % 10 + '0';
	length += ft_print_char(c);
	return (length);
}
