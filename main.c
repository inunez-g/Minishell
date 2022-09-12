/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:51:26 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/09 13:21:11 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtins(t_struct *data, int mode)
{
	if (echo_func(*data, mode))
		return (1);
	else if (exit_func(*data, mode))
		return(1);
	else if (env_func(*data, mode))
		return(1);
	else if (pwd_func(*data, mode))
		return(1);
	else if (cd_func(data, mode))
		return (1);
	else if (export_func(data, mode))
		return(1);
	else if (unset_func(data, 0, mode))
		return(1);
	return(0);
}

int commands_func(t_struct *data)
{
	char	*final_path;
	char	**path;
	char	*command;
	int		pos;
	int		i;

	i = 0;
	command = ft_strjoin("/", data->cmd[0]);
	pos = super_strncmp(data->env, "PATH=", 5);
	path= ft_split(data->env[pos] + 5, ':');
	while(path[i] != NULL)
	{
		final_path = ft_strjoin(path[i], command);
		if (access(final_path, X_OK) == -1)
		{
			free(final_path);
			i++;
		}
		else
		{
			//printf("HOLA\n");
			execve(ft_strjoin(path[i],command), data->cmd, data->env);
		}
	}
	write(1, "command not found\n", 18);
	exit (0);
}

int export_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return(i);
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

void    executions_func(t_struct *data, int mode)
{
    int pid;
    int status;

    if (activation_func(data, mode))
    {
		pipe(data->fd);
        pid = fork();
        if (pid == -1)
            return ;
        if (pid == 0)
        {
           	ft_outfile(data);
			ft_infile(data);
			pipes_func(data, mode);;
			if (!builtins(data, 1))
	    		commands_func(data);
			exit (0);
        }
        else
        {
            waitpid(pid, &status, 0);
			close(data->fd[1]);
			data->status = WEXITSTATUS(status);
			if (data->inpipe != -1)
				close(data->inpipe);
			data->inpipe = data->fd[0];
			data->fd_outfile = -1;
			data->fd_infile = -1;
        }
    }
}

// MAIN FUNC

int main(int argc, char **argv, char **env)
{
	char *str;
	t_struct data;
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

void	write_pipe(int fd)
{
	char c;
	int	size;

	size = 0;
	do
	{
		write(0, &c, size);
		size = read(fd, &c, 1);
		ft_putnbr_fd(size, 0);
	}while (size ==1);
}

/*
int main(int argc, char **argv, char **env)
{
	char *str;
	t_struct data;
	struct sigaction	sa;
	(void)argc;
	(void)argv;

	sa.sa_flags = 0; 
    sa.sa_mask = 0;
    rl_catch_signals = 0;
	sa.sa_sigaction = sighandler;
	sigaction(SIGINT, &sa, NULL);
	data.env = super_dup(env);
	int fd = open("temp.txt", O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	int pipes[2];
	int	infile = 0;
	pipe(pipes);
	//pipes[1] = fd;
	while (1)
	{
		str = readline("nice> ");
		dup2(pipes[0], STDIN_FILENO);
		dup2(pipes[1], infile);
		printf("[%s]", str);
		dup2(infile, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
	//	write_pipe(pipes[1]);
		
		//	str = readline("consola> ");
		//dup2(pipes[0], STDOUT_FILENO);
	//	ft_putnbr_fd(STDOUT_FILENO, 0);
	//	ft_putnbr_fd(pipes[0], 0);
	//	ft_putnbr_fd(pipes[1], 0);
	//	ft_putnbr_fd(fd, 0);
		//dup2(fd, pipes[1]);
		//dup2(0, STDOUT_FILENO);
		//close(pipes[0]);
	//	dup2(fd, STDOUT_FILENO);
		exit (0);
		if (!str)
			exit (0);
		if (str[0] == '\0')
		{
			free(str);
			continue ;
		}
		free(str);
	}
	return (0);
}*/
