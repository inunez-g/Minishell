/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:43:05 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/23 21:36:43 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (signal == SIGQUIT)
		return ;
	if (signal == 0)
		exit (0);
	if (signal == 2 && g_proccess == 0)
	{
		ft_new_line();
		//printf("aaaaaa\n");
	}
	if (signal == 2 && (g_proccess == 1 || g_proccess == 2))
	{
		
	}
}
