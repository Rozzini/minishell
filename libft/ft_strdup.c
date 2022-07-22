/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 08:53:10 by mraspors          #+#    #+#             */
/*   Updated: 2021/12/22 08:53:12 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*str;
	int		i;

	i = 0;
	while (string[i] != '\0')
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
