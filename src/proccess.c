/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:35:54 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 18:16:59 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_struct *data, int mode)
{
	if (echo_func(*data, mode))
		return (1);
	else if (exit_func(*data, mode))
		return (1);
	else if (env_func(*data, mode))
		return (1);
	else if (pwd_func(*data, mode))
		return (1);
	else if (cd_func(data, mode))
		return (1);
	else if (export_func(data, mode))
		return (1);
	else if (unset_func(data, 0, mode))
		return (1);
	return (0);
}

int	commands_func(t_struct *data)
{
	char	*final_path;
	char	**path;
	char	*command;
	int		pos;
	int		i;

	i = 0;
	if (data->cmd[0] == NULL)
		exit (0);
	command = ft_strjoin("/", data->cmd[0]);
	pos = super_strncmp(data->env, "PATH=", 5);
	path = ft_split(data->env[pos] + 5, ':');
	while (path[i] != NULL)
	{
		final_path = ft_strjoin(path[i], command);
		if (access(final_path, X_OK) == -1)
		{
			free(final_path);
			i++;
		}
		else
			execve(ft_strjoin(path[i], command), data->cmd, data->env);
	}
	write(1, "command not found\n", 18);
	exit (0);
}

int	activation_func(t_struct *data, int mode)
{
	if (mode != 3)
		return (1);
	if (!builtins(data, 0))
		return (1);
	ft_outfile(data);
	ft_infile(data);
	builtin_pipe(data);
	return (0);
}

void	executions_func(t_struct *data, int mode)
{
	int	pid;
	int	status;

	if (activation_func(data, mode))
	{
		pipe(data->fd);
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			g_proccess = 2;
			close(data->fd[0]);
			ft_infile(data);
			ft_outfile(data);
			if (mode == 0)
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
			if (mode == 1)
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
			if (mode == 2 || mode == 3)
			{
				write_pipe(data->fd_infile);
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
			if (!builtins(data, 1))
				commands_func(data);
			exit (0);
		}
		else
		{
			close(data->fd[1]);
			waitpid(pid, &status, 0);
			g_proccess = 1;
			data->status = WEXITSTATUS(status);
			data->inpipe = data->fd[0];
			data->fd_outfile = -1;
			data->fd_infile = -1;
		}
	}
}
