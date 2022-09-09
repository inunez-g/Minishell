/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_clean_funcs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:29:14 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/09 09:45:18 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipes(t_struct *data, char *str)
{
	int		i;
	char	**cmd2;

	cmd2 = ft_split2(str, '|');
	i = 0;
	while (cmd2[i])
	{
		data->fd_infile = -1;
		data->fd_outfile = -1;
		if (super_strlen(cmd2) == 1)
			prepare_data(data, cmd2[i], 3);
		else if (super_strlen(cmd2) == 1 || i == super_strlen(cmd2) - 1)
			prepare_data(data, cmd2[i], 2);
		else if (i == 0)
			prepare_data(data, cmd2[i], 0);
		else
			prepare_data(data, cmd2[i], 1);
		i++;
	}
}

void	prepare_data(t_struct *data, char *str, int mode)
{
	int		i;
	char	*helper;

	data->inpipe = -1;
	data->cmd = NULL;
	data->infile = NULL;
	data->outfile = NULL;
	data->cmd = (char **)malloc(sizeof(char *) * (check_nbr_cmd(str) + 1));
	data->infile = (char **)malloc(sizeof(char *)
			* (check_nbr_pointers(str, 60) + 1));
	data->infile_modes = (int *)malloc(sizeof(int)
			* check_nbr_pointers(str, 60));
	data->outfile = (char **)malloc(sizeof(char *)
			* (check_nbr_pointers(str, 62) + 1));
	data->outfile_modes = (int *)malloc(sizeof(int)
			* check_nbr_pointers(str, 62));
	save_in_outfiles(data, str, 60);
	save_in_outfiles(data, str, 62);
	save_cmd(data, str);
	i = 0;
	/*printf("EMPIEZA\n");
	super_printf(data->cmd);
	printf("TERMINA\n");*/
	while (data->cmd[i] != NULL)
	{
		helper = expand_variables(data, data->cmd[i]);
		data->cmd[i] = helper;
		i++;
	}
	printf("CMD[%s]:\n",str);
	super_printf(data->cmd);
	printf("INFILES:\n");
	super_printf(data->infile);
	printf("OUTFILES:\n");
	super_printf(data->outfile);
	executions_func(data, mode);
}

char	*clean_path_func(char *path)
{
	char	*clean_path;
	int		i;
	int		j;
	int		index;

	i = 1;
	index = 0;
	j = 0;
	clean_path = ft_calloc(ft_strlen(path) + 1, sizeof(char));
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			if (path[i + 1] == '.' && path[i + 2] == '.')
			{
				i += 3;
				index = i;
			}
			else
			{
				while (index < i)
				{
					clean_path[j] = path[index];
					j++;
					index++;
				}
				i++;
			}
		}
		else
			i++;
		if (path[i] == '\0')
		{
			while (index < i)
			{
				clean_path[j] = path[index];
				j++;
				index++;
			}
		}
	}
	return (clean_path);
}
/*
char	*clean_path_func(char *clean_path, char path, int *i, int *index, int *j
			if (path[i + 1] == '.' && path[i + 2] == '.')
            {
                i += 3;
                index = i;
            }
            else
            {
                while (index < i)
                {
                    clean_path[j] = path[index];
                    j++;
                    index++;
                }
                i++;
            }
*/
