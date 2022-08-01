/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:01:04 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/28 00:40:59 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//add new node to list
void	push(t_env **head_ref, char *key, char *val)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->val = NULL;
	if (val != NULL)
		new_node->val = ft_strdup(val);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

//free node memory and remove it
// free(temp->key);
	// free(temp->val);
void	delete_head(t_env **head)
{
	t_env	*temp;

	temp = *head;
	*head = (*head)->next;
	free(temp->key);
	if (temp->val != NULL)
		free(temp->val);
	free(temp);
}

//removes provided noded
void	delete_node(t_env *node)
{
	t_env	*temp;

	temp = node->next;
	node->next = temp->next;
	free(temp->key);
	if (temp->val != NULL)
		free(temp->val);
	free(temp);
}

int	count_nodes(t_env **head)
{
	t_env	*temp;
	int		count;

	temp = *head;
	count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
