/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/22 23:10:07 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **av)
{
	int	i;

	i = 1;
	if (ft_strncmp("echo", av[0], 6) == 0)
	{
		while (av[i] != NULL)
		{
			printf("%s", av[i]);
			printf("%c", 32);
			i++;
		}
	}
}

void	ft_pwd(int ac, char **av)
{
	if (ft_strncmp("pwd", av[1], 4) == 0)
	{
		printf("%s", getcwd(NULL, 0));
	}
}

void	ft_cd(int ac, char **av)
{
	if (ft_strncmp("cd", av[1], 2) == 0)
	{
		printf("%d\n", chdir(av[2]));
	}
}