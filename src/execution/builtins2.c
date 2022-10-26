/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:22:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/26 18:33:02 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_cmd *cmd, t_env **env_list)
{
	if (ft_strcmp("env", cmd->args[0]) == 0)
	{
		print_env(env_list);
		return (0);
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;
	int		i;

	i = 1;
	if (ft_strcmp("unset", cmd->args[0]) == 0)
	{
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
		return (0);
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	if (ft_strcmp("exit", cmd->args[0]) == 0)
	{
		free_doublptr(cmd->args);
		free(cmd);
		free_list(env_list);
<<<<<<< HEAD
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
=======
>>>>>>> a38892c213958d44ac70d1e921bae6a554d2c134
		exit(0);
	}
	return (1);
}
