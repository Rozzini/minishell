/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/24 22:12:25 by mraspors         ###   ########.fr       */
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
	if (ft_strcmp("pwd", tokens->args[0]) == 0)
	{
		printf("%s\n", getcwd(NULL, 0));
		return (0);
	}
	return (1);
}

int	ft_cd(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	t_env	*old_temp;

	if (ft_strcmp("cd", tokens->args[0]) == 0)
	{
		if (chdir(tokens->args[1]) == -1)
			return (0);
		temp = find_node_by_key(*env_list, "PWD");
		old_temp = find_node_by_key(*env_list, "OLDPWD");
		old_temp->val = ft_strdup(temp->val);
		temp->val = getcwd(NULL, 0);
		return (0);
	}
	return (1);
}
