/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/17 19:10:20 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_func(t_struct *data, int mode)
{
	if (mode == 0)
		mode0_pipe(data);
	else if (mode == 1)
		mode1_pipe(data);
	else if (mode == 2 || mode == 3)
		mode2_pipe(data);
}

void	builtin_pipe(t_struct *data)
{
	//printf("builtin_pipe\n");
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
	builtins(data, 1);
	close(data->fd_infile);
	close(data->fd_outfile);
	close(data->inpipe);
	close(data->fd[0]);
	close(data->fd[1]);
	dup2(0, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
}

void	mode2_pipe(t_struct *data)
{
	//printf("mode2\n");
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	else
		dup2(data->inpipe, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
}

void mode1_pipe(t_struct *data)
{
	printf("mode1\n");
	dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
	{
        dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
	}
    else
        dup2(data->fd[1], STDOUT_FILENO);
}

void	mode0_pipe(t_struct *data)
{
	//printf("mode0\n");
	close(data->fd[0]);
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
	else
		dup2(data->fd[1], STDOUT_FILENO);
}
