/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:51:26 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/09 09:59:48 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("command not found\n");
	exit (0);
}

int	export_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
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
	//builtins(data, 1);
	//close(data->inpipe);
	//close(data->fd[0]);
	//close(data->fd[1]);
	return (0);
}

void	executions_func(t_struct *data, int mode)
{
	int	pid;
	int	status;
	int	fd[2];

	if (activation_func(data, mode))
	{
		//printf("holaaa\n");
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			ft_outfile(data);
			ft_infile(data);
			pipes_func(data, mode);
			if (!builtins(data, 1))
				commands_func(data);
		
		//printf("holaaa\n");
		}
		else
		{
			waitpid(pid, &status, 0);
			if (data->inpipe != -1)
				close(data->inpipe);
			data->inpipe = fd[0];
			close(fd[1]);
			if (mode == 2)
				close(fd[0]);
			data->fd_outfile = -1;
			data->fd_infile = -1;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	char				*str;
	t_struct			data;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_flags = 0;
	sa.sa_mask = 0;
	rl_catch_signals = 0;
	sa.sa_sigaction = sighandler;
	sigaction(SIGINT, &sa, NULL);
	data.env = super_dup(env);
	while (1)
	{
		str = readline("consola> ");
		if (!str)
			exit (0);
		if (str[0] == '\0')
		{
			free(str);
			continue ;
		}
		add_history(str);
		prepare_pipes(&data, str);
		free(str);
	}
	return (0);
}

void	ft_new_line(void)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(int signal, siginfo_t *a, void *b)
{
	(void)a;
	(void)b;
	if (signal == 0)
		exit (0);
	if (signal == 2)
	{
		ft_new_line();
	}
}
