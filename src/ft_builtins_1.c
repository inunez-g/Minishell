/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:04:59 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/23 20:03:51 by ecamara          ###   ########.fr       */
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

void	cd2(t_struct *data, int *pos2, int *pos, char *path)
{
	*pos2 = super_strncmp(data->env, "OLDPWD=", 7);
	if (*pos2 != -1)
		free (data->env[*pos2]);
	else
	{
		change(data);
		*pos2 = super_strlen(data->env);
	}
	*pos = super_strncmp(data->env, "PWD=", 4);
	if (*pos != -1)
		free (data->env[*pos]);
	else
	{
		change(data);
		*pos = super_strlen(data->env);
	}
	data->env[*pos2] = ft_strjoin("OLDPWD=", path);
	printf("[%s]\n", data->env[*pos2]);
}

int	cd3(t_struct *data, char **final_path, int pos, char **path)
{
	if (chdir(*final_path) == -1)
	{
		write(2, ": No such file or directory\n", 28);
		free(*final_path);
		free (path);
		data->status = 1;
		return (1);
	}
	free(*path);
	*path = getcwd(NULL, 1024);
	data->env[pos] = ft_strjoin("PWD=", *path);
	free (*path);
	free (*final_path);
	return (1);
}

void	cd4(t_struct *data, char **final_path, char **path)
{
	if (data->cmd[1][0] == '/')
		*final_path = ft_strdup(data->cmd[1]);
	else
	{
		*final_path = ft_strjoin(*path, "/");
		*final_path = strjoin_ms(*final_path, data->cmd[1], 0);
		*final_path = clean_path_func(*final_path, 1, 0, 0);
	}
}

void	cd5(t_struct *data, char **final_path, int pos2)
{
	*final_path = ft_substr(data->env[pos2], 7, ft_strlen(data->env[pos2]) - 7);
	write(0, *final_path, ft_strlen(*final_path));
	write(0, "\n", 1);
}

int	cd_func(t_struct *data, int mode, int pos2)
{
	char	*path;
	char	*final_path;
	int		pos;

	if (!strncmp_ms(data->cmd[0], "cd"))
	{
		if (mode == 0 || data->cmd[1] == NULL)
			return (1);
		path = getcwd(NULL, 1024);
		if (data->cmd[1][0] == '-')
		{
			if (data->cmd[1][1] != '\0')
				return (error6(data, data->cmd[1], 1, 1));
			pos2 = super_strncmp(data->env, "OLDPWD=", 7);
			if (pos2 == -1)
				return (error7(data, 1, 1));
			else
				cd5(data, &final_path, pos2);
		}
		else 
			cd4(data, &final_path, &path);
		cd2(data, &pos, &pos2, path);
		return (cd3(data, &final_path, pos, &path));
	}
	return (0);
}
