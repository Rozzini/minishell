/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:09:14 by mraspors          #+#    #+#             */
/*   Updated: 2022/03/20 18:48:09 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_helper(unsigned int num, char c)
{
	int		length;
	int		reminder;
	char	symbol;

	reminder = 0;
	length = 0;
	reminder = num % 16;
	if (reminder < 10)
		symbol = reminder + '0';
	else
	{
		if (c == 'x')
			symbol = reminder - 10 + 'a';
		if (c == 'X')
			symbol = reminder - 10 + 'A';
	}
	if (num >= 16)
		length += ft_print_hex(num / 16, c);
	length += ft_print_char(symbol);
	return (length);
}

int	ft_print_hex(unsigned int num, char c)
{
	int	length;

	length = 0;
	if (num == 0)
		return (ft_print_char('0'));
	else
		length += ft_hex_helper(num, c);
	return (length);
}
