/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 11:57:35 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_func(t_struct *data, int mode)
{
	g_proccess = 2;
	close(data->fd[0]);
	ft_infile(data);
	ft_outfile(data);
	if (mode == 0)
		mode0_pipe(data);
	if (mode == 1)
		mode1_pipe(data);
	if (mode == 2 || mode == 3)
		mode2_pipe(data);
	if (!builtins(data, 1))
		commands_func(data);
	exit (0);
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
	if (data->error)
	{
		dup2(0, STDOUT_FILENO);
		dup2(0, STDIN_FILENO);
		return ;
	}
	builtins(data, 1);
	dup2(0, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
}

void	mode2_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		close(data->fd_infile);
	}
	else
		dup2(data->inpipe, 0);
	if (data->fd_outfile != -1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
	close(data->fd[1]);
}

void	mode1_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		close(data->fd_infile);
	}
	else
		dup2(data->inpipe, 0);
	if (data->fd_outfile != -1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
	else
		dup2(data->fd[1], 1);
	close(data->fd[1]);
}

void	mode0_pipe(t_struct *data)
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
	else
		dup2(data->fd[1], 1);
	close (data->fd[1]);
}
