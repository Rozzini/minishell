/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:05:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/23 20:25:05 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_export_extra(t_tokens *tokens, t_env **env_list, char *equal, int i)
{
	t_env	*temp;
	char	*key;
	char	*val;

	val = ft_strchr(tokens->args[i], '+');
	if (val == NULL)
	{
		key = ft_substr(tokens->args[i], 0,
				ft_strlen(tokens->args[i]) - ft_strlen(equal));
		temp = find_node_by_key(*env_list, key);
		if (temp == NULL)
			push(env_list, key, &equal[1]);
		else
			temp->val = &equal[1];
	}
	else
	{
		key = ft_substr(tokens->args[i], 0,
				ft_strlen(tokens->args[i]) - ft_strlen(val));
		temp = find_node_by_key(*env_list, key);
		if (temp == NULL)
			push(env_list, key, &equal[1]);
		else
			ft_strcat(temp->val, &equal[1]);
	}	
}

void	do_export(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	char	*equal;
	int		i;

	i = 1;
	while (i < tokens->arg_c)
	{
		equal = ft_strchr(tokens->args[i], '=');
		if (equal == NULL)
		{
			temp = find_node_by_key(*env_list, tokens->args[i]);
			if (temp == NULL)
				push(env_list, tokens->args[i], NULL);
		}
		else
			do_export_extra(tokens, env_list, equal, i);
		i++;
	}
}

int	ft_export(t_tokens *tokens, t_env **env_list)
{
	if (ft_strcmp("export", tokens->args[0]) == 0)
	{
		if (tokens->arg_c == 1)
			print_env_export(env_list);
		else
			do_export(tokens, env_list);
		return (0);
	}
	return (1);
}
