/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:58:19 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 21:21:49 by mraspors         ###   ########.fr       */
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