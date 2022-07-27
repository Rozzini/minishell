/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:57:31 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/27 19:32:09 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//checks for opened quotes first if everything fine
//splits string and saves each argument and
//also amount of arguments to tokens structure
int	basic_parsing(t_tokens *tokens)
{
	if (tokens->cmdl[0] == '\0')
		return (1);
	add_history(tokens->cmdl);
	if (check_q(tokens->cmdl) == 1)
		return (1);
	tokens->arg_c = 0;
	tokens->args = ft_split(tokens->cmdl, ' ');
	if (tokens->args == NULL)
		return (1);
	while (tokens->args[tokens->arg_c] != NULL)
		tokens->arg_c++;
	return (0);
}

int	check_minishell_exec(t_tokens *tokens, t_env **env)
{
	int		pid;
	int		i;
	static int j = 1;
	char	*str_cut;
	char	**env_s;
	t_env	*shlvl;

	shlvl = find_node_by_key(*env, "SHLVL");
	i = 0;
	if (tokens->cmdl[0] == '.' && tokens->cmdl[1] == '/')
	{
		j++;
		shlvl->val = ft_itoa(j);
		env_s = env_list_to_string(*env);
		str_cut = malloc(ft_strlen(tokens->cmdl) - 2);
		while (tokens->cmdl[i + 2] != '\0')
		{
			str_cut[i] = tokens->cmdl[i + 2];
			i++;
		}
		str_cut[i] = '\0';
		pid = fork();
		if (pid == 0)
		{
			if (execve(str_cut, NULL, env_s) == -1)
				free(str_cut);
		}
		wait(0);
		free(str_cut);
		return (1);
	}
	return (0);
}
