/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:40:29 by mraspors          #+#    #+#             */
/*   Updated: 2021/12/31 12:40:29 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_count(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			counter++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (counter);
}

char	*ft_add_word(char const *s, int start, int end)
{
	int		i;
	char	*word;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		var[3];
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	while (s[var[0]] != '\0')
	{
		if (s[var[0]] != c)
		{
			var[2] = var[0];
			while (s[var[0]] != c && s[var[0]] != '\0')
				var[0]++;
			result[var[1]++] = ft_add_word(s, var[2], var[0]);
		}
		else
			var[0]++;
	}
	result[var[1]] = NULL;
	return (result);
}
