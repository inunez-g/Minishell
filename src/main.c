/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:51:26 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/17 19:10:02 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int export_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return(i);
}

static void	init_data(struct sigaction *sa, t_struct *data, char **env)
{
	sa->sa_flags = 0; 
    sa->sa_mask = 0;
    rl_catch_signals = 0;
	sa->sa_sigaction = sighandler;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
	data->env = super_dup(env);
}

int main(int argc, char **argv, char **env)
{
	char				*str;
	t_struct 			data;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	init_data(&sa, &data, env);
	while (1)
	{
		g_proccess = 0;
		str = readline("consola> ");
		g_proccess = 1;
		if (!str)
			exit (0);
		if (str[0] == '\0')
		{
			free(str);
			continue ;
		}
		add_history(str);
		input(&data, str);
		free(str);
	}
	return (0);
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
