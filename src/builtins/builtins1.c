/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/23 14:35:54 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_tokens *tokens)
{
	int	i;

	i = 1;
	if (ft_strncmp("echo", tokens->args[0], 6) == 0)
	{
		while (tokens->args[i] != NULL)
		{
			printf("%s", tokens->args[i]);
			printf("%c", 32);
			i++;
		}
	}
}

void	ft_pwd(t_tokens *tokens)
{
	if (ft_strncmp("pwd", tokens->args[1], 4) == 0)
	{
		printf("%s", getcwd(NULL, 0));
	}
}

void	ft_cd(t_tokens *tokens)
{
	if (ft_strncmp("cd", tokens->args[1], 2) == 0)
	{
		printf("%d\n", chdir(tokens->args[2]));
	}
}