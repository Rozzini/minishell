/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 08:19:11 by mraspors          #+#    #+#             */
/*   Updated: 2021/12/22 08:51:37 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*pointer;
	size_t	i;

	if (nitems == 0 || size == 0)
	{
		pointer = malloc(nitems * size);
		pointer[0] = '\0';
		return (pointer);
	}
	pointer = malloc(nitems * size);
	if (!pointer)
		return (NULL);
	i = 0;
	while (i < nitems * size)
		pointer[i++] = '\0';
	return (pointer);
}
