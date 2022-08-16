/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:46:37 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/05 11:03:08 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mode3_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	else
		dup2(data->fd[1], STDIN_FILENO);
}

/*void mode2_pipe(t_struct *data)
{

}*/

/*void mode1_pipe(t_struct *data)
{

}*/

void	mode0_pipe(t_struct *data)
{
	if (data->fd_infile != -1)
		dup2(data->fd_infile, STDIN_FILENO);
	if (data->fd_outfile != -1)
		dup2(data->fd_outfile, STDOUT_FILENO);
}

void	ft_oufile(t_struct *data)
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
