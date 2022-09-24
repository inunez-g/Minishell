/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 10:50:38 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 10:52:08 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error7(t_struct *data, int mode, int ret)
{
	write(2, "bash: cd: OLDPWD not set\n", 26);
	data->status = mode;
	return (ret);
}

int	error8(t_struct *data, char *str, int mode)
{
	(void)data;
	write(2, "bash: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 21);
	exit(mode);
}

int	check_2(t_struct *data, char *str, int i, int mode)
{
	if (str[i] == '=' && mode == 0)
	{
		error3(data, data->cmd[0], str, 1);
		return (1);
	}
	if (str[i] == '\0' && mode == 1)
		return (1);
	if (str[i] == '\0' && mode == 0)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			error3(data, data->cmd[0], str, 1);
			return (1);
		}
	}
	return (0);
}

int	check_export(t_struct *data, char *str, int mode)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		error3(data, data->cmd[0], str, 1);
		return (1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			error3(data, data->cmd[0], str, 1);
			return (1);
		}
	}
	return (check_2(data, str, i, mode));
}

void	error_free(char *str, t_struct *data)
{
	write(2, str, ft_strlen(str));
	if (data->cmd)
		free (data->cmd);
	if (data->infile)
		free (data->infile);
	if (data->infile_modes)
		free (data->infile_modes);
	if (data->outfile_modes)
		free (data->outfile_modes);
	if (data->outfile)
		free (data->outfile);
}
