/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:57:31 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/23 14:40:32 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     basic_parsing(t_tokens *tokens)
{
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