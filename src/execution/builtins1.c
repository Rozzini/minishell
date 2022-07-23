/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/23 14:55:05 by mraspors         ###   ########.fr       */
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
		{
			printf("%s", tokens->args[i]);
			printf("%c", 32);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_pwd(t_tokens *tokens)
{
	if (ft_strcmp("pwd", tokens->args[0]) == 0)
	{
		printf("%s", getcwd(NULL, 0));
		return (0);
	}
	return (1);
}

int	ft_cd(t_tokens *tokens)
{
	if (ft_strcmp("cd", tokens->args[0]) == 0)
	{
		printf("%d\n", chdir(tokens->args[1]));
		return (0);
	}
	return (1);
}