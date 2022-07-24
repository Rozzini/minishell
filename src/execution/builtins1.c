/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/24 13:29:00 by mrizk            ###   ########.fr       */
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
			printf("%s\n", tokens->args[i]);
			// printf("%c", 32);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_pwd(t_tokens *tokens)
{
	char	*mini;

	if (ft_strcmp("pwd", tokens->args[0]) == 0)
	{
		printf("%s", getcwd(NULL, 0));
		return (0);
	}
	return (1);
}

int	ft_cd(t_tokens *tokens)
{
	char	*str;

	if (ft_strcmp("cd", tokens->args[0]) == 0)
	{
		if ((tokens->args[1]) == NULL)
		{
			chdir("/Users/mrizk");
			return (0);
		}
		chdir(tokens->args[1]);
		return (0);
	}
	return (1);
}
