/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:05:19 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/22 17:39:59 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_func_body(t_struct *data, int pos)
{
	char	*path;
	char	*final_path;

	path = ft_substr(data->env[pos], 4, ft_strlen(data->env[pos]) - 4);
	final_path = ft_strjoin(path, "/");
	free(path);
	return (final_path);
}

int	unset_func_body(t_struct *data, int i, int line)
{
	char	**new_env;
	int		j;
	int		size;

	size = super_strlen(data->env);
	free(data->env[line]);
	data->env[line] = NULL;
	new_env = (char **)malloc(sizeof(char *) * (size));
	j = 0;
	while (data->env[j] != NULL)
	{
		new_env[j] = data->env[j];
		j++;
	}
	j++;
	while (data->env[j] != NULL)
	{
		new_env[j - 1] = data->env[j];
		j++;
	}
	new_env[j - 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (i);
}

int	unset_func(t_struct *data, int helper, int mode)
{
	int	i;
	int	line;

	i = 1;
	if (!strncmp_ms(data->cmd[0], "unset") || helper == 1)
	{
		if (mode == 0)
			return (1);
		while (data->cmd[i])
		{
			line = super_strncmp(data->env, data->cmd[i],
					export_helper(data->cmd[i]));
			if (line != -1)
				i = unset_func_body(data, i, line);
			i++;
		}
		return (1);
	}
	return (0);
}

int	export_func_body(t_struct *data, int i)
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
	new_env[j] = data->cmd[i];
	new_env[j + 1] = NULL;
	free(data->env);
	data->env = new_env;
	i++;
	return (i);
}

void	show_export(t_struct *data)
{
	int	i;

	i = 0;
	while(data->env[i])
	{
		printf("declare -x %s\n", data->env[i]);
		i++;
	}
}

int	export_func(t_struct *data, int mode)
{
	int	i;

	i = 1;
	if (!strncmp_ms(data->cmd[0], "export"))
	{
		if (mode == 0)
			return (1);
		if (data->cmd[1] == NULL)
			show_export(data);
		unset_func(data, 1, 1);
		while (data->cmd[i])
			i = export_func_body(data, i);
		return (1);
	}
	return (0);
}
