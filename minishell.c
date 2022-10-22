/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/22 16:36:41 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_cmd		*cmd;
	t_tokens	*tokens;
	char		**path;

	env_list = NULL;
	cmd = NULL;
	argc = 0;
	if (argv == NULL)
		argc++;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	path = ft_split(find_node_by_key(env_list, "PATH")->val, ':');
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			try_execute(&cmd, &env_list, path);
			free(tokens->cmdl);
			free_cmd(&cmd);
			free_doublptr(tokens->args);
		}		
	}
	return (0);
}
