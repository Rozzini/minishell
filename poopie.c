#include "minishell.h"

int	ft_2d_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char **update_args(t_cmd *cmd, int in_out)
{
	int		i;
	int 	j;
	char 	**updated_args;

	i = 0;
	if (in_out == 0)
	{
		updated_args = malloc(sizeof(char *) * (ft_2d_size(cmd->args) + ft_2d_size(cmd->input->args) + 1));
		while (cmd->args[i])
		{
			updated_args[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		j = 0;
		while (cmd->input->args[j])
		{
			updated_args[i] = ft_strdup(cmd->input->args[j]);
			j++;
			i++;
		}
		updated_args[i][0] = '\0';
	}
	else
	{
		updated_args = malloc(sizeof(char *) * (ft_2d_size(cmd->args) + ft_2d_size(cmd->output->args) + 1));
		while (cmd->args[i])
		{
			updated_args[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		j = 0;
		while (cmd->output->args[j])
		{
			updated_args[i] = ft_strdup(cmd->output->args[j]);
			j++;
			i++;
		}
		updated_args[i][0] = '\0';
	}
	
	return (updated_args);
}

int main()
{



}
