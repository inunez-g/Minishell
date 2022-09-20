/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:51:26 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/20 19:59:21 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
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

int	main(int argc, char **argv, char **env)
{
	char				*str;
	t_struct			data;
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
	char	c;
	
	while (1)
	{
		int i = read(fd, &c, 1);
		if (i == 0 || i == -1)
			break ;
		write (0, &c, 1);
	}
}
