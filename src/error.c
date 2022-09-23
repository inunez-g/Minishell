/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:44:30 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/23 20:47:16 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error2(t_struct *data, char *str, int mode, int activation)
{
	write(2, "bash: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 29);
	if (activation == 1)
		exit(mode);
	else
		data->status = mode;
}

int	error3(t_struct *data, char *str, char *str2, int mode)
{
	write(2, "bash: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": `", 4);
	write(2, str2, ft_strlen(str2));
	write(2, "': not a valid identifier\n", 27);
	data->status = mode;
	return (1);
}

void	error4(t_struct *data, char c, int mode)
{
	write(2, "bash: unexpected EOF while looking for matching `", 50);
	write(2, &c, 1);
	write(2, "'\nbash: syntax error: unexpected end of file\n", 46);
	data->status = mode;
}

void	error5(t_struct *data, int mode, char *str, int end)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, str, 1);
	write(2, "'\n", 2);
	if (!end)
		data->status = mode;
	else
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

int	error6(t_struct *data, char *str, int mode, int ret)
{
	write(2, "bash: cd: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": invalid option\n", 18);
	data->status = mode;
	return (ret);
}

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
