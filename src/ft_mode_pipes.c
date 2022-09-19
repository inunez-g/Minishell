/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/18 19:10:32 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_func(t_struct *data, int mode, int fd[2])
{
	if (mode == 0)
		mode0_pipe(data, fd);
	else if (mode == 1)
		mode1_pipe(data, fd);
	else if (mode == 2 || mode == 3)
		mode2_pipe(data, fd);
}

void	builtin_pipe(t_struct *data)
{
	//printf("builtin_pipe\n");
	if (data->fd_infile != -1)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		close(data->fd_infile);
	}
	if (data->fd_outfile != -1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
	builtins(data, 1);
	close(data->inpipe);
	close(data->fd[0]);
	close(data->fd[1]);
	dup2(0, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
}

void	mode2_pipe(t_struct *data, int fd[2])
{
	//printf("mode2\n");
	//close(data->fd[1]);
	//if (data->fd_infile != -1)
	//	dup2(data->fd_infile, STDIN_FILENO);
//	else
	dup2(data->inpipe, STDIN_FILENO);
//	if (data->fd_outfile != -1)
//		dup2(data->fd_outfile, STDOUT_FILENO);
	close(data->inpipe);
	close(fd[1]);
}

void mode1_pipe(t_struct *data, int fd[2])
{
	printf("mode1\n");
	dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
	{
        dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
    else
        dup2(fd[1], STDOUT_FILENO);
}

void	mode0_pipe(t_struct *data, int fd[2])
{
	(void)data;
	//printf("mode0\n");
	//if (data->fd_infile != -1)
	//	dup2(data->fd_infile, STDIN_FILENO);
//	if (data->fd_outfile != -1)
//		dup2(data->fd_outfile, STDOUT_FILENO);
//	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}
