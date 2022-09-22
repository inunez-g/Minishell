/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:04:59 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/22 19:18:07 by ecamara          ###   ########.fr       */
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

	if (!strncmp_ms(data.cmd[0], "pwd") && ft_strlen(data.cmd[0]) == 3)
	{
		if (mode == 0)
			return (1);
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

int	cd_func(t_struct *data, int mode)
{
	char	*path;
	char	*final_path;
	int		pos;
	int		pos2;

	if (!strncmp_ms(data->cmd[0], "cd"))
	{
		if (mode == 0 || data->cmd[1] == NULL)
			return (1);
		if (data->cmd[1][0] == '-')
		{
			if (data->cmd[1][1] != '\0')
			{
				printf("bash: cd: %s: invalid option\n", data->cmd[1]);
				data->status = 1;
				return (1);
			}
			pos2 = super_strncmp(data->env, "OLDPWD=", 7);
			if (pos2 == -1)
			{
				printf("bash: cd: OLDPWD not set\n");
				data->status = 1;
				return (1);
			}
			else
			{
				final_path = ft_substr(data->env[pos2], 7, ft_strlen(data->env[pos2]) - 7);
				/*chdir(path);
				if (chdir(path) == -1)
				{
					write(2, ": No such file or directory\n", 28);
					data->status = 1;
				}
				else
				{
					printf("%s\n", getcwd(path, 1024));
				}
				free (path);
				return (1);*/
			}
		}
		pos2 = super_strncmp(data->env, "OLDPWD=", 7);
		if (pos2 != -1)
			free (data->env[pos2]);
		else
		{
			change(data);
			pos2 = super_strlen(data->env);
		}
		pos = super_strncmp(data->env, "PWD=", 4);
		if (pos != -1)
			free (data->env[pos]);
		else
		{
			change(data);
			pos = super_strlen(data->env);
		}
		if (data->cmd[1][0] == '/')
			final_path = ft_strdup(data->cmd[1]);
		else
		{
			path = getcwd(NULL, 0);
			final_path = ft_strjoin(path, "/");
			final_path = strjoin_ms(final_path, data->cmd[1], 0);
			final_path = clean_path_func(final_path, 1, 0, 0);
		}
		data->env[pos2] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		data->env[pos] = ft_strjoin("PWD=", final_path);
		if (chdir(final_path) == -1)
		{
			write(2, ": No such file or directory\n", 28);
			free(final_path);
			data->status = 1;
			return (1);
		}
		free (final_path);
		return (1);
	}
	return (0);
}
