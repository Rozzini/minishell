/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:31:15 by mrizk             #+#    #+#             */
/*   Updated: 2022/07/22 22:28:01 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

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

void	pwd(int ac, char **av)
{
	if (ft_strncmp("pwd", av[1], 4) == 0)
	{
		printf("%s", getcwd(NULL, 0));
	}
}

void	cd(int ac, char **av)
{
	if (ft_strncmp("cd", av[1], 2) == 0)
	{
		printf("%d\n", chdir(av[2]));
	}
}

int	main(int ac, char **av)
{

}
