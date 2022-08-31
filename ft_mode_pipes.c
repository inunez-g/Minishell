/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/30 13:17:12 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_func(t_struct *data, int mode)
{
	if (mode == 0)
		mode0_pipe(data);
	else if (mode == 1)
		mode1_pipe(data);
	else if (mode == 2)
		mode2_pipe(data);
}

void    builtin_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
        dup2(data->fd_infile, STDIN_FILENO);
    if (data->fd_outfile != -1)
        dup2(data->fd_outfile, STDOUT_FILENO);
	builtins(data, 1);
    close(data->inpipe);
    close(data->fd[0]);
    close(data->fd[1]);
}

void	mode2_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->inpipe);
	close(data->fd[1]);
}

void mode1_pipe(t_struct *data)
{
	dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
        dup2(data->fd_outfile, STDOUT_FILENO);
    else
        dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->inpipe);
	close(data->fd[1]);
}

void	mode0_pipe(t_struct *data)
{
	close(data->fd[0]);
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
	else
		dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
}

void	ft_outfile(t_struct *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->outfile[i])
	{
		if (data->outfile_modes[i] == 1)
			fd = open(data->outfile[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(data->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->outfile[i + 1] == NULL)
			data->fd_outfile = fd;
		else
			close(fd);
		i++;
	}
    //moverse outfile
    //mode append
    //open
    //si es ultimo guardas fd en data->fd_outfile
}

void    ft_infile(t_struct *data)
{
    int i;
    int fd;
	int fd2[2];
	char	*temp;
	char	*str;

	str = "";
    i = 0;
    while (data->infile[i])
    {
        if (data->infile_modes[i] == 1)
		{
            fd = open(data->infile[i], O_RDONLY, 0644);
			if (data->infile[i + 1] == NULL)
            	data->fd_infile = fd;
			close(fd);
		}
        else
		{
			temp = readline("> ");
			while (strncmp(temp, data->infile[i], ft_strlen(data->infile[i])))
			{
				str = ft_strjoin(str, temp);
				str = ft_strjoin(str, "\n");
				free(temp);
				temp = readline("> ");
			}
			free(temp);
			if (data->infile[i + 1] == NULL)
			{
				pipe(fd2);
				write(fd2[1], str, ft_strlen(str));
				data->fd_infile = fd2[0];
			}
			close(fd2[1]);
		}
        i++;
    }
    //moverse outfile
    //mode append
    //open
    //si es ultimo guardas fd en data->fd_outfile
}
