/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/22 20:48:01 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		x;
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (s1[i] == s2[i] && i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
		{
			i++;
		}
		x = (unsigned char)s1[i] - (unsigned char)s2[i];
		return (x);
	}
}

void	echo(int ac, char **av)
{
	int	i;

	i = 2;
	if (ft_strncmp("echo", av[1], 6) == 0)
	{
		while (i < ac)
		{
			printf("%s", av[i]);
			printf("%c", 32);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	echo(ac, av);
}
