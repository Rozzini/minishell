/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:48 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/29 21:45:36 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_doublptr(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
	s = NULL;
}

void	free_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	while (temp != NULL)
	{
		delete_head(list);
		temp = *list;
	}
}
