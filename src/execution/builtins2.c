/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:22:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/28 22:46:56 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_tokens *tokens, t_env **env_list)
{
	if (ft_strcmp("env", tokens->args[0]) == 0)
	{
		print_env(env_list);
		return (0);
	}
	return (1);
}

int	ft_unset(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	int		i;

	i = 1;
	if (ft_strcmp("unset", tokens->args[0]) == 0)
	{
		while (i < tokens->arg_c)
		{
			temp = *env_list;
			if (ft_strcmp(temp->key, tokens->args[i]) == 0)
				delete_head(env_list);
			temp = find_node_by_key_del(*env_list, tokens->args[i]);
			if (temp != NULL)
				delete_node(temp);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_exit(t_tokens *tokens, t_env **env_list)
{
	if (ft_strcmp("exit", tokens->args[0]) == 0)
	{
		free_doublptr(tokens->args);
		free(tokens);
		free_list(env_list);
		exit(0);
	}
	return (1);
}
