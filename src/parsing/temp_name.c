/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:57:31 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/19 16:56:45 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	check_minishell_exec(t_tokens *tokens, t_env **env)
// {
// 	int		pid;
// 	int		i;
// 	static int j = 1;
// 	char	*str_cut;
// 	char	**env_s;
// 	t_env	*shlvl;

// 	shlvl = find_node_by_key(*env, "SHLVL");
// 	i = 0;
// 	if (tokens->cmdl[0] == '.' && tokens->cmdl[1] == '/')
// 	{
// 		j++;
// 		shlvl->val = ft_itoa(j);
// 		env_s = env_list_to_string(*env);
// 		str_cut = malloc(ft_strlen(tokens->cmdl) - 2);
// 		while (tokens->cmdl[i + 2] != '\0')
// 		{
// 			str_cut[i] = tokens->cmdl[i + 2];
// 			i++;
// 		}
// 		str_cut[i] = '\0';
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (execve(str_cut, env_s, env_s) == -1)
// 				free(str_cut);
// 		}
// 		wait(0);
// 		free(str_cut);
// 		return (1);
// 	}
// 	return (0);
// }
int	check_minishell_exec(t_tokens *tokens, t_env **env)
{
	reutrn (0);
}
