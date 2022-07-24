/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:44:21 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/24 21:05:29 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_env(t_env *env)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = env;
	while (temp != NULL)
	{
		if (temp->val != NULL)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	*ft_str(char *key, char *val)
{
	char	*str;
	int		i;

	i = 0;
	if (val == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(val) + 2));
	while (i < ft_strlen(key) + ft_strlen(val) + 1)
	{
		while (*key != '\0')
			str[i++] = *(key++);
		str[i++] = '=';
		while (*val != '\0')
			str[i++] = *(val++);
	}
	str[i] = '\0';
	return (str);
}

char	**env_list_to_string(t_env *env)
{
	char	**env_s;
	t_env	*temp;
	int		i;
	char	*s;

	i = 0;
	temp = env;
	env_s = (char **)malloc(sizeof(char *) * (count_env(env) + 1));
	while (temp != NULL)
	{
		if (temp->val != NULL)
		{
			env_s[i] = ft_str(temp->key, temp->val);
			temp = temp->next;
			i++;
		}
	}
	env_s[i] = NULL;
	return (env_s);
}
