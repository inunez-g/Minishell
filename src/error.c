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

int	error6(t_struct *data, char *str, int mode, int ret)
{
	write(2, "bash: cd: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": invalid option\n", 18);
	data->status = mode;
	return (ret);
}
