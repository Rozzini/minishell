/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 23:09:24 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*line;
	char	**args;
	int i = 0;

	env_list = NULL;
	init_env_list(&env_list, env);
	while (1)
	{
		line = readline("");
		args = ft_split(line, ' ');
		ft_echo(args);
	}
    return (0);
}
