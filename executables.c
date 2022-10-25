/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:25:09 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/24 18:31:47 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int		ft_execs(t_tokens *tokens, char **env)
{
	char cmd[] = "/usr/bin/";
	char *str = ft_strjoin(cmd, tokens->args[0]);

	char *argVec[] = {tokens->args[0], tokens->args[1], NULL};
	if (execve(str, argVec, env) == -1)
	{
		free (str);
		str = ft_strjoin("/bin/", tokens->args[0]);
		if (execve(str, argVec, env) == -1)
			printf("mininshell: %s: command not found either\n", tokens->args[0]);
		printf("mininshell: %s: command not found\n", tokens->args[0]);
	}
	return (0);
}
