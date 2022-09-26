/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 10:56:06 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 10:56:08 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd2(t_struct *data, int *pos2, int *pos, char *path)
{
	*pos2 = super_strncmp(data->env, "OLDPWD=", 7);
	*pos = super_strncmp(data->env, "PWD=", 4);
	if (*pos2 != -1)
		free (data->env[*pos2]);
	else
	{
		change(data);
		*pos2 = super_strlen(data->env);
	}
	if (*pos != -1)
		free (data->env[*pos]);
	else
	{
		change(data);
		*pos = super_strlen(data->env);
	}
	if (!ft_strncmp(path, "/Users", ft_strlen(path)))
		data->env[*pos2] = ft_strdup("OLDPWD=/");
	else
		data->env[*pos2] = ft_strjoin("OLDPWD=", path);
}

int	cd3(t_struct *data, char **final_path, int pos, char **path)
{
	int	temp;

	temp = chdir(*final_path);
	if (!ft_strncmp(data->cmd[1], "..", ft_strlen(data->cmd[1])) && temp == -1)
	{
		data->env[pos] = ft_strdup("PWD=/");
		free (*final_path);
		free (*path);
		return (1);
	}
	if (temp == -1)
	{
		write(2, ": No such file or directory\n", 28);
		free(*final_path);
		free (*path);
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

int	cd_func(t_struct *data, int mode, int pos, int pos2)
{
	char	*path;
	char	*final_path;

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
		cd2(data, &pos2, &pos, path);
		return (cd3(data, &final_path, pos, &path));
	}
	return (0);
}
