/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:51:26 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/23 21:02:03 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (mega_checker(&data, str))
		{
			free (str);
			continue ;
		}
		input(&data, str);
		free(str);
	}
	return (0);
}
