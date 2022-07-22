/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:08:33 by mraspors          #+#    #+#             */
/*   Updated: 2022/03/20 18:48:19 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_string(char *str)
{
	int	i;
	int	length;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		length += ft_print_char(str[i]);
		i++;
	}
	return (length);
}
