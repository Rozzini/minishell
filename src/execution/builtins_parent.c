/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/11/15 04:37:17 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		exit_check_arg(char *s)
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

int		ft_exit(t_cmd *cmd, t_env **env_list)
{
	int	n;

	if (cmd->args == NULL)
		return (0);
	if (ft_strcmp("exit", cmd->args[0]) == 0)
	{
		n = 0;
		if (cmd->arg_c > 2)
		{
			printf("minishell:  exit: too many arguments\n");
			return (1);
		}
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
	if (home == NULL)
		return ;
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

	if (find_node_by_key(*env_list, "PWD") == NULL
			|| find_node_by_key(*env_list, "OLDPWD") == NULL)
		return (1);
	if (cmd->arg_c == 1)
	{
		ft_cd_helper(env_list);
		g_signal = 0;
		return (1);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		g_signal = 1;
		return (1);
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
