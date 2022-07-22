/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:29:03 by mraspors          #+#    #+#             */
/*   Updated: 2021/06/28 17:56:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i[4];

	i[0] = ft_strlen(dst);
	i[1] = ft_strlen(src);
	i[2] = ft_strlen(dst) + ft_strlen(src);
	i[3] = 0;
	if (!dstsize)
		return (i[1]);
	if (i[0] > dstsize)
		return (dstsize + i[1]);
	while (src[i[3]] && i[0] < dstsize - 1)
		dst[i[0]++] = src[i[3]++];
	dst[i[0]] = '\0';
	return (i[2]);
}
