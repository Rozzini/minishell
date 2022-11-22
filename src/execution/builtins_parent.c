/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/11/20 23:24:41 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_check_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	int	n;

	if (cmd->args == NULL)
		return (0);
	if (ft_strcmp("exit", cmd->args[0]) == 0)
	{
		n = 0;
		if (ft_exit_helper(cmd) == 1)
			return (1);
		printf("exit\n");
		if (cmd->args[1] != NULL)
		{
			if (ft_strlen(cmd->args[1]) > 10
				|| exit_check_arg(cmd->args[1]))
				printf("minishell: exit: %s: numeric argument required\n",
					cmd->args[1]);
			else
				n = ft_atoi(cmd->args[1]);
		}
		free_cmd(&cmd);
		free_list(env_list);
		exit(n);
	}
	return (0);
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
	g_global.signal = 0;
	return (1);
}

void	ft_cd_helper(t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;
	t_env	*home;

	home = find_node_by_key(*env_list, "HOME");
	if (home == NULL)
		return ;
	temp = find_node_by_key(*env_list, "PWD");
	old_temp = find_node_by_key(*env_list, "OLDPWD");
	free(old_temp->val);
	old_temp->val = ft_strdup(temp->val);
	chdir(home->val);
	free(temp->val);
	temp->val = getcwd(NULL, 0);
}

int	ft_cd(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;

	if (find_node_by_key(*env_list, "PWD") == NULL
		|| find_node_by_key(*env_list, "OLDPWD") == NULL)
		return (1);
	if (ft_cd_error(cmd, env_list) == 1)
		return (1);
	temp = find_node_by_key(*env_list, "PWD");
	old_temp = find_node_by_key(*env_list, "OLDPWD");
	free(old_temp->val);
	old_temp->val = ft_strdup(temp->val);
	free(temp->val);
	temp->val = getcwd(NULL, 0);
	g_global.signal = 0;
	return (1);
}
