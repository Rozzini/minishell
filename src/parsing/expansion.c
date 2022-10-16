/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/16 19:42:13 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_expansion_pointers(t_parsing *prs)
{
	int	i;

	i = 0;
	while (prs->exp_name[i] != NULL)
		i++;
	return (i);
}

int		copy_expansion_name(char *s, t_parsing *prs, int i)
{
	int			start;

	i++;
	start = i;
	if (ft_isdigit(s[i]) == 0)
	{
		while (is_separator(s[i]) == 0 && ft_isalnum(s[i]) == 1 && s[i] != '\0')
			i++;
	}
	else
		i++;
	prs->exp_name[prs->iter] = ft_substr(&s[start], 0, ft_strlen(&s[start]) - ft_strlen(&s[i]));
	prs->iter++;
	return (i);
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
	int		j;
	int		c;
	char	*s;
	t_env	*temp;

	i = 0;
	c = 0;
	j = 0;
	if (prs->og_token[j] == 34)
		j++;
	while (prs->exp_name[c] != NULL)
	{
		if (prs->og_token[j] == 34)
			j++;
		if (prs->og_token[j] == 39)
		{
			j++;
			while (prs->og_token[j] != 39)
			{
				i++;
				j++;
			}
			j++;
		}
		if (prs->token[i] == '$')
		{
			temp = check_expansion_name(prs->exp_name[c], env);
			s = ft_substr(prs->token, 0,
				ft_strlen(prs->token) - ft_strlen(&(prs->token[i])));
			if (temp != NULL)
		 		s = ft_strjoin(s, temp->val);
			s = ft_strjoin(s, &(prs->token[i + 1 + ft_strlen(prs->exp_name[c])]));
			free(prs->token);
			prs->token = s;
			if (temp != NULL)
				i += ft_strlen(temp->val) - 1;
			j += ft_strlen(prs->exp_name[c]);
			c++;
		}
		i++;
		j++;
	}
}