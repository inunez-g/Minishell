/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:26:51 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 11:26:57 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    write_pipe(int fd)
{
    char    c;

	while (1)
	{
		int temp = read(fd, &c, 1);
		if (temp == 0 || temp == -1)
			break ;
		printf("[%c]", c);
	}
}

void	here_dock(t_struct *data, int i)
{
	int	pid;
	int	status;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		infile_helper(data, i, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		g_proccess = 1;
		data->inpipe = fd[0];
	}
}
