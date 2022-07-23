/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:57:31 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/23 20:28:38 by mraspors         ###   ########.fr       */
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
