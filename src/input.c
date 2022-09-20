/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:29:14 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/20 19:34:29 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input(t_struct *data, char *str)
{
	int		i;
	char	**cmd;

	cmd = ft_split2(str, '|');
	i = 0;
	while (cmd[i])
	{
		data->fd_infile = -1;
		data->fd_outfile = -1;
		if (super_strlen(cmd) == 1)
			prepare_data(data, cmd[i], 3);
		else if (super_strlen(cmd) == 1 || i == super_strlen(cmd) - 1)
			prepare_data(data, cmd[i], 2);
		else if (i == 0)
			prepare_data(data, cmd[i], 0);
		else
			prepare_data(data, cmd[i], 1);
		i++;
	}
	free_memory(cmd);
}

void	mallocs(t_struct *data, char *str)
{
	data->cmd = (char **)malloc(sizeof(char *) * (check_nbr_cmd(str) + 1));
	if (!data->cmd)
		error_free("Malloc error", data);
	data->cmd[check_nbr_cmd(str)] = NULL;
	data->infile = (char **)malloc(sizeof(char *)
			* (check_nbr_pointers(str, 60) + 1));
	if (!data->infile)
		error_free("Malloc error", data);
	data->cmd[check_nbr_pointers(str, 60)] = NULL;
	data->infile_modes = (int *)malloc(sizeof(int)
			* check_nbr_pointers(str, 60));
	if (!data->infile_modes)
		error_free("Malloc error", data);
	data->outfile = (char **)malloc(sizeof(char *)
			* (check_nbr_pointers(str, 62) + 1));
	if (!data->outfile)
		error_free("Malloc error", data);
	data->outfile[check_nbr_pointers(str, 62)] = NULL;
	data->outfile_modes = (int *)malloc(sizeof(int)
			* check_nbr_pointers(str, 62));
	if (!data->outfile_modes)
		error_free("Malloc error", data);
}

void	expand_all(t_struct *data)
{
	char 	*temp;
	int		i;

	i = -1;
	while (data->cmd[++i] != NULL)
	{
		temp = expand_variables(data, data->cmd[i]);
		free  (data->cmd[i]);
		data->cmd[i] = temp;
	}
	i = -1;
	while (data->infile[++i] != NULL)
	{
		temp = expand_variables(data, data->infile[i]);
		free  (data->infile[i]);
		data->infile[i] = temp;
	}
	i = -1;
	while (data->outfile[++i] != NULL)
	{
		temp = expand_variables(data, data->outfile[i]);
		free (data->outfile[i]);
		data->outfile[i] = temp;
	}
}

void	prepare_data(t_struct *data, char *str, int mode)
{
	//data->inpipe = -1;
	data->cmd = NULL;
	data->infile = NULL;
	data->outfile = NULL;
	mallocs(data, str);
	save_in_outfiles(data, str, 60);
	save_in_outfiles(data, str, 62);
	save_cmd(data, str);
	expand_all(data);
	executions_func(data, mode);
	free_memory(data->cmd);
	free_memory(data->infile);
	free_memory(data->outfile);
	free(data->infile_modes);
	free(data->outfile_modes);
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
