/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:35:54 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/23 21:25:44 by ecamara          ###   ########.fr       */
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
	else if (cd_func(data, mode, 0, 0))
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
	error8(data, data->cmd[0], 127);
	return (0);
}

int	activation_func(t_struct *data, int mode)
{
	data->error = 0;
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
			pipes_func(data, mode);
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
