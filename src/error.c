/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:44:30 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/17 19:10:34 by ecamara          ###   ########.fr       */
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

void	error3(t_struct *data, char *str, char *str2, int mode)
{
	printf("bash: %s: `%s': not a valid identifier\n", str, str2);
	data->status = mode;
}

void	error4(t_struct *data, char c, int mode)
{
	printf("bash: unexpected EOF while looking for matching `%c'", c);
	printf("\n");
	data->status = mode;
}

void    error5(t_struct *data, int mode)
{
	write(1, "bash: syntax error near unexpected token `>'\n", 45);
    data->status = mode;
}

int	check_export(t_struct *data, char *str, int mode)
{
	int	i;

	i = 0;
//	printf("check[%s]\n", str);
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