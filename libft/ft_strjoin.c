/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:52:57 by mraspors          #+#    #+#             */
/*   Updated: 2021/12/23 15:06:16 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_l;
	int		s2_l;

	if (!s1 || !s2)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_l);
	ft_memcpy(&str[s1_l], s2, s2_l);
	str[s1_l + s2_l] = '\0';
	return (str);
}
