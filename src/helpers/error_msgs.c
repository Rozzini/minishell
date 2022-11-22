/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:58:19 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 22:37:58 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	er_rdr_no_file(char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": No such file or directory\n", 28);
	return (-1);
}

void	er_ft_execs(char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": command not found\n", 20);
}

int	is_all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_separator(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_parsing_err(t_tokens *tokens)
{
	if (is_all_spaces(tokens->cmdl) == 1)
	{
		free(tokens->cmdl);
		free(tokens);
		return (1);
	}
	add_history(tokens->cmdl);
	if (check_q(tokens->cmdl) == 1)
	{
		free(tokens->cmdl);
		free(tokens);
		return (1);
	}
	return (0);
}

void	create_pwd(t_env **env)
{
	t_env	*temp;
	t_env	*old_temp;
	t_env	*home;

	home = find_node_by_key(*env, "HOME");
	if (home == NULL)
		return ;
	temp = find_node_by_key(*env, "PWD");
	old_temp = find_node_by_key(*env, "OLDPWD");
	if (temp == NULL)
		push(env, "PWD", home->val);
	if (old_temp == NULL)
		push(env, "OLDPWD", home->val);
}
