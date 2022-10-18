/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:17:51 by alalmazr          #+#    #+#             */
/*   Updated: 2022/10/17 12:18:06 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int n_cmds(t_cmd *head)
{
	int count = 0;
	t_cmd *current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}