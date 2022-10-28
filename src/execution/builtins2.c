/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:22:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/28 22:43:19 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_cmd *cmd, t_env **env_list)
{
	print_env(env_list);
	free_cmd(&cmd);
	free_list(env_list);
	exit(0);
}

void	ft_unset(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;
	int		i;

	i = 1;
	while (i < cmd->arg_c)
	{
		temp = *env_list;
		if (ft_strcmp(temp->key, cmd->args[i]) == 0)
			delete_head(env_list);
		temp = find_node_by_key_del(*env_list, cmd->args[i]);
		if (temp != NULL)
			delete_node(temp);
		i++;
	}
	free_cmd(&cmd);
	free_list(env_list);
	exit(0);
}

void	ft_exit(t_cmd *cmd, t_env **env_list)
{
	char	*s;

	s = NULL;
	if (cmd->args != NULL)
		s = cmd->args[0];
	else
		return ;
	if (ft_strcmp("exit", s) == 0)
	{
		free_cmd(&cmd);
		free_list(env_list);
		exit(0);
	}
}
