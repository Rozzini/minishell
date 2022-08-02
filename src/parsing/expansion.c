/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/02 08:53:11 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//checks if there is such key name in env list
//return 1 if there is no such key, 0 if found smthing
// int	check_expansion_name(char *start, char *end, t_env **env)
// {
// 	char	*name;
// 	t_env	*temp;

// 	name = ft_substr(start, 1, ft_strlen(start) - ft_strlen(end));
// 	temp = find_node_by_key(*env, name);
// 	free(name);
// 	if (temp == NULL)
// 		return (1);
// 	return (0);
// }

// char	*do_expansion(char *s, char *start, char *end, t_env **env)
// {
// 	char	*result;
// 	char	*name;
// 	t_env	*temp;

// 	result = NULL;
// 	name = ft_substr(start, 1, ft_strlen(start) - ft_strlen(end));
// 	temp = find_node_by_key(*env, name);
// 	free(name);
// 	if (s != start)
// 		result = ft_substr(s, 0, ft_strlen(s) - ft_strlen(start));
// 	if (s != start)
// 		ft_strjoin(result, temp->val);
// 	else
// 		result = ft_strdup(temp->val);
// 	ft_strjoin(result, end);
// 	return (result);
// }

//char	*remove_expansion(char *s, char *start, char *end)
// char	*remove_expansion(void)
// {
// 	return (NULL);
// }

// char	*iterate_expansion(char	*string)
// {
// 	char	*s;

// 	s = string;
// 	while (is_separator(*s) == 0 && *s != '\0')
// 		s++;
// 	return (s);
// }

// char	*try_expansion(char *string, char *exp_p_start, t_env **env)
// {
// 	char	*p;
// 	char	*s;
// 	char	*exp_p_end;

// 	p = string;
// 	s = string;
// 	exp_p_end = iterate_expansion(exp_p_start);
// 	if (check_expansion_name(p, exp_p_end, env) == 0)
// 		return (do_expansion(p, exp_p_start, exp_p_end, env));
// 	else
// 		return (remove_expansion());
// }

// void	check_expansion(t_tokens *tokens, t_env **env)
// {
// 	int		i;
// 	char	*exp_p;

// 	i = 0;
// 	while (tokens->args[i] != NULL)
// 	{
// 		exp_p = ft_strchr(tokens->args[i], '$');
// 		if (exp_p != NULL)
// 			tokens->args[i] = try_expansion(tokens->args[i], exp_p, env);
// 		i++;
// 	}
// }
