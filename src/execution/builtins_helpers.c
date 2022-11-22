/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 22:56:34 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 23:07:11 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	try_parent_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("exit", cmd->args[0]) == 0)
			return (ft_exit(cmd, env));
		if (ft_strcmp("cd", cmd->args[0]) == 0)
			return (ft_cd(cmd, env));
		else if (ft_strcmp("unset", cmd->args[0]) == 0)
			return (ft_unset(cmd, env));
		else if (ft_strcmp("export", cmd->args[0]) == 0)
			return (ft_export(cmd, env));
	}
	return (0);
}

int	try_child_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("export", cmd->args[0]) == 0)
			return (print_env_export(env));
		if (ft_strcmp("pwd", cmd->args[0]) == 0)
			return (ft_pwd());
		if (ft_strcmp("echo", cmd->args[0]) == 0)
			return (ft_echo(cmd));
		if (ft_strcmp("env", cmd->args[0]) == 0)
			return (ft_env(env));
	}
	return (0);
}

int	ft_cd_error(t_cmd *cmd, t_env **env_list)
{
	if (cmd->arg_c == 1 || ft_strcmp(cmd->args[1], "~") == 0)
	{
		ft_cd_helper(env_list);
		g_global.signal = 0;
		return (1);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, "\n", 1);
		g_global.signal = 1;
		return (1);
	}
	return (0);
}

int	ft_exit_helper(t_cmd *cmd)
{
	if (cmd->arg_c > 2)
	{
		printf("minishell:  exit: too many arguments\n");
		return (1);
	}
	return (0);
}
