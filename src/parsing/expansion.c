/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/19 16:36:40 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_expansion_pointers(t_parsing *prs)
{
	int	i;

	i = 0;
	while (prs->expansions_p[i] != -1)
		i++;
	return (i);
}

char	*copy_expansion_name(char *s, t_parsing *prs, int i)
{
	char	*start;

	s++;
	start = s;
	while (is_separator(*s) == 0 && *s != '\0' && *s != 34)
		s++;
	prs->exp_name[i] = ft_substr(start, 0, ft_strlen(start) - ft_strlen(s));
	return (s);
}

t_env	*check_expansion_name(char *name, t_env **env)
{
	t_env	*temp;

	temp = find_node_by_key(*env, name);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

void	do_expansion(t_parsing	*prs, t_env **env)
{
	int		i;
	int		pointer;
	char	*s;
	t_env	*temp;

	i = count_expansion_pointers(prs) - 1;
	while (i >= 0)
	{
		temp = check_expansion_name(prs->exp_name[i], env);
		pointer = prs->expansions_p[i];
		s = ft_substr(prs->token, 0,
				ft_strlen(prs->token) - ft_strlen(&(prs->token[pointer])));
		if (temp != NULL)
			s = ft_strjoin(s, temp->val);
		pointer = prs->expansions_p[i] + 1;
		s = ft_strjoin(s, &(prs->token[pointer]));
		free(prs->token);
		prs->token = s;
		i--;
	}
}
