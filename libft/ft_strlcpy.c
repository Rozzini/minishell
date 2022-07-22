/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:37:02 by mraspors          #+#    #+#             */
/*   Updated: 2021/12/22 14:37:05 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = (size_t)ft_strlen(src);
	if (dstsize > 0)
	{
		while (i < dstsize - 1)
		{
			if (src[i] != '\0')
				dst[i] = src[i];
			else
				break ;
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
