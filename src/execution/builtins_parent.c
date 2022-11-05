/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/11/06 02:21:12 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_cmd *cmd, t_env **env_list)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("exit", cmd->args[0]) == 0)
		{
			free_cmd(&cmd);
			free_list(env_list);
			exit(0);
		}
	}
}

int	ft_unset(t_cmd *cmd, t_env **env_list)
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
	g_signal = 0;
	return (1);
}

void	ft_cd_helper(t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;
	t_env	*home;
	char	*s;

	home = find_node_by_key(*env_list, "HOME");
	temp = find_node_by_key(*env_list, "PWD");
	old_temp = find_node_by_key(*env_list, "OLDPWD");
	free(old_temp->val);
	old_temp->val = ft_strdup(temp->val);
	s = getcwd(NULL, 0);
	while (ft_strcmp(s, home->val) != 0)
	{
		chdir("..");
		free(s);
		s = getcwd(NULL, 0);
	}
	free(s);
	free(temp->val);
	temp->val = getcwd(NULL, 0);
}

int	ft_cd(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;

	if (cmd->arg_c == 1)
	{
		ft_cd_helper(env_list);
		exit(0);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		exit(-1);
	}
	temp = find_node_by_key(*env_list, "PWD");
	old_temp = find_node_by_key(*env_list, "OLDPWD");
	free(old_temp->val);
	old_temp->val = ft_strdup(temp->val);
	free(temp->val);
	temp->val = getcwd(NULL, 0);
	g_signal = 0;
	return (1);
}
