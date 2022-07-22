/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 23:28:28 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*line;
	char	**args;
	int i = 0;
	char *s = getcwd(NULL, 0);
	strcat(s, "$ ");
	env_list = NULL;
	init_env_list(&env_list, env);
	while (1)
	{
		line = readline(s);
		args = ft_split(line, ' ');
		ft_echo(args);
	}
    return (0);
}
