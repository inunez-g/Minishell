/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:04:59 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/23 20:58:17 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_func(t_struct data, int mode)
{
	int	i;

	i = 1;
	if (!strncmp_ms(data.cmd[0], "echo"))
	{
		if (mode == 0)
			return (1);
		if (data.cmd[1] != NULL && !strncmp_ms(data.cmd[1], "-n")
			&& data.cmd[1][0] != '\0')
			i = 2;
		while (data.cmd[i] != NULL)
		{
			printf("%s", data.cmd[i++]);
			if (data.cmd[i] != NULL || (data.cmd[i - 1][0] == '\0'
				&& data.cmd[i]))
				printf(" ");
		}
		if (strncmp_ms(data.cmd[1], "-n") || data.cmd[1][0] == '\0')
			printf("\n");
		return (1);
	}
	return (0);
}

int	exit_func(t_struct data, int mode)
{
	if (!strncmp_ms(data.cmd[0], "exit"))
	{
		if (mode == 0)
			return (1);
		if (checkexit(data.cmd[1], &data))
			return (1);
		write(2, "exit\n", 5);
		if (data.cmd[1] != NULL)
			exit(ft_atoi(data.cmd[1]));
		else
			exit(0);
	}
	return (0);
}

int	env_func(t_struct data, int mode)
{
	int	i;

	i = 0;
	if (!strncmp_ms(data.cmd[0], "env"))
	{
		if (mode == 0)
			return (1);
		while (data.env[i] != NULL)
			printf("%s\n", data.env[i++]);
		return (1);
	}
	return (0);
}

int	pwd_func(t_struct data, int mode)
{
	char	path[1024];
	int		pos;

	if (!strncmp_ms(data.cmd[0], "pwd") && ft_strlen(data.cmd[0]) == 3)
	{
		if (mode == 0)
			return (1);
		pos = super_strncmp(data.env, "PWD=", 4);
		if (pos != -1)
			printf("%s\n", data.env[pos] + 4);
		else
			printf("%s\n", getcwd(path, 1024));
		return (1);
	}
	return (0);
}

void	change(t_struct *data)
{
	char	**new_env;
	int		size;
	int		j;

	size = super_strlen(data->env);
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	j = 0;
	while (data->env[j] != NULL)
	{
		new_env[j] = data->env[j];
		j++;
	}
	new_env[j] = NULL;
	new_env[j + 1] = NULL;
	free(data->env);
	data->env = new_env;
}
