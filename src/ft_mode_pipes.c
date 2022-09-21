/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/21 18:12:58 by inunez-g         ###   ########.fr       */
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
	dup2(0, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);	
}

void	mode2_pipe(t_struct *data, int fd[2])
{
	ft_putnbr_fd(4567890, 2);
	(void)fd;
	dup2(data->inpipe, 0);
	close(fd[1]);
	close (fd[0]);
}

void mode1_pipe(t_struct *data, int fd[2])
{
	dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
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
	//close(fd[1]);
	
	/*if (data->inpipe != -1)
		dup2(data->inpipe, STDIN_FILENO);
	if (data->outpipe != -1)
		dup2(data->outpipe, STDOUT_FILENO);
	else*/
	//dup2(data->inpipe, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
}
