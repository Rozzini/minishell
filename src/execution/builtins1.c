/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/10/11 06:35:42 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (ft_strcmp("echo", cmd->args[0]) == 0)
	{
		if (ft_strcmp(cmd->args[1], "-n") == 0)
		{
			flag = 1;
			i = 2;
		}	
		while (cmd->args[i] != NULL)
			printf("%s ", cmd->args[i++]);
		if (flag == 0)
			printf("\n");
		return (0);
	}
	return (1);
}

int	ft_pwd(t_cmd *cmd)
{
	char	*s;

	if (ft_strcmp("pwd", cmd->args[0]) == 0)
	{
		s = getcwd(NULL, 0);
		printf("%s\n", s);
		free(s);
		return (0);
	}
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

	if (ft_strcmp("cd", cmd->args[0]) == 0)
	{
		if (cmd->arg_c == 1)
		{
			ft_cd_helper(env_list);
			return (0);
		}
		if (chdir(cmd->args[1]) == -1)
			return (0);
		temp = find_node_by_key(*env_list, "PWD");
		old_temp = find_node_by_key(*env_list, "OLDPWD");
		free(old_temp->val);
		old_temp->val = ft_strdup(temp->val);
		free(temp->val);
		temp->val = getcwd(NULL, 0);
		return (0);
	}
	return (1);
}
