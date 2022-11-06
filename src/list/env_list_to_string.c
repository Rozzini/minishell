/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:44:21 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/01 15:11:15 by mraspors         ###   ########.fr       */
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
		count++;
		temp = temp->next;
	}
	return (count);
}

char	*ft_str(char *key, char *val)
{
	char	*str;
	char	*str_eq;

	if (val == NULL)
		str = ft_strjoin(key, "=");
	else
	{
		str_eq = ft_strjoin(key, "=");
		str = ft_strjoin(str_eq, val);
		free(str_eq);
	}
	return (str);
}

char	**env_list_to_string(t_env *env)
{
	char	**env_s;
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	env_s = malloc(sizeof(char *) * (count_env(env) + 1));
	while (temp != NULL)
	{
		env_s[i] = ft_str(temp->key, temp->val);
		temp = temp->next;
		i++;
	}
	env_s[i] = NULL;
	return (env_s);
}
