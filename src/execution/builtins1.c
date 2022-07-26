/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/27 02:38:43 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_tokens *tokens)
{
	int	i;

	i = 1;
	if (ft_strcmp("echo", tokens->args[0]) == 0)
	{
		while (tokens->args[i] != NULL)
			printf("%s ", tokens->args[i++]);
		printf("\n");
		return (0);
	}
	return (1);
}

int	ft_pwd(t_tokens *tokens)
{
	char	*s;

	if (ft_strcmp("pwd", tokens->args[0]) == 0)
	{
		s = getcwd(NULL, 0);
		printf("%s\n", s);
		free(s);
		return (0);
	}
	return (1);
}

void	ft_cd_helper(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;
	char	*s;

	temp = find_node_by_key(*env_list, "PWD");
	old_temp = find_node_by_key(*env_list, "OLDPWD");
	free(old_temp->val);
	old_temp->val = ft_strdup(temp->val);
	s = getcwd(NULL, 0);
	while (ft_strstr(s, "Desktop") != NULL)
	{
		chdir("..");
		free(s);
		s = getcwd(NULL, 0);
	}
	free(s);
	free(temp->val);
	temp->val = getcwd(NULL, 0);
}

int	ft_cd(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;

	if (ft_strcmp("cd", tokens->args[0]) == 0)
	{
		if (tokens->arg_c == 1)
		{
			ft_cd_helper(tokens, env_list);
			return (0);
		}
		if (chdir(tokens->args[1]) == -1)
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
