/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:04:59 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/08 20:10:40 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_func(t_struct data)
{
	int	i;

	i = 1;
	if (!strncmp(data.cmd[0], "echo", ft_strlen(data.cmd[0])))
	{
		if (!strncmp(data.cmd[1], "-n", ft_strlen(data.cmd[1])))
			i = 2;
		while (data.cmd[i] != NULL)
		{
			printf("%s", data.cmd[i++]);
			if (data.cmd[i] != NULL)
				printf(" ");
		}
		if (strncmp(data.cmd[1], "-n", ft_strlen(data.cmd[1])))
			printf("\n");
		return (1);
	}
	return (0);
}

int	exit_func(t_struct data)
{
	if (!strncmp(data.cmd[0], "exit", ft_strlen(data.cmd[0])))
	{
		if (data.cmd[1] != NULL)
			exit(ft_atoi(data.cmd[1]));
		else
			exit(0);
	}
	return (0);
}

int	env_func(t_struct data)
{
	int	i;

	i = 0;
	if (!strncmp(data.cmd[0], "env", ft_strlen(data.cmd[0])))
	{
		while (data.env[i] != NULL)
			printf("%s\n", data.env[i++]);
		return (1);
	}
	return (0);
}

int	pwd_func(t_struct data)
{
	int	pos;

	if (!strncmp(data.cmd[0], "pwd", 3) && ft_strlen(data.cmd[0]) == 3)
	{
		pos = super_strncmp(data.env, "PWD=", 4);
		if (pos != -1)
			printf("%s\n", data.env[pos] + 4);
		return (1);
	}
	return (0);
}

int	cd_func(t_struct *data)
{
	char	*path;
	char	*final_path;
	int		pos;

	if (!strncmp(data->cmd[0], "cd", ft_strlen(data->cmd[0])))
	{
		path = data->cmd[1];
		pos = super_strncmp(data->env, "PWD=", 4);
		if (path[0] != '/')
		{
			final_path = cd_func_body(data, pos);
			path = ft_strjoin(final_path, data->cmd[1]);
		}
		final_path = clean_path_func(path);
		if (chdir(final_path) == -1)
		{
			write(2, ": No such file or directory\n", 28);
			free(final_path);
			return (1);
		}
		free(data->env[pos]);
		data->env[pos] = ft_strjoin("PWD=", final_path);
		return (1);
	}
	return (0);
}
