/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:04:27 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 11:04:29 by inunez-g         ###   ########.fr       */
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

void	show_export(t_struct *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("declare -x %s\n", data->env[i]);
		i++;
	}
}

int	checkexit(char *str, t_struct *data)
{
	int	i;

	if (str == NULL)
		return (0);
	if (super_strlen(data->cmd + 1) != 1)
	{
		write (2, "exit \nbash: exit: too many arguments\n", 37);
		data->status = 1;
		return (1);
	}
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			write (2, "exit \nbash: exit: ", 18);
			write (2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			exit (255);
		}
	}
	return (0);
}

int	checkpath(t_struct *data)
{
	int	pos;

	pos = super_strncmp(data->env, "PATH=", 5);
	if (pos == -1)
	{
		error2(data, data->cmd[0], 127, 1);
		exit(127);
	}
	return (pos);
}
