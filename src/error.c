/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:44:30 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/22 11:37:22 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error2(t_struct *data, char *str, int mode, int activation)
{
	printf("bash: %s: No such file or directory\n", str);
	if (activation == 1)
		exit(mode);
	else
		data->status = mode;
}

int	error3(t_struct *data, char *str, char *str2, int mode)
{
	printf("bash: %s: `%s': not a valid identifier\n", str, str2);
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

void	error_free(char *str, t_struct *data)
{
	(void)data;
	(void)str;
}
