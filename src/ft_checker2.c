/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:10:11 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/24 11:10:13 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pikito_args_checker2(t_struct *data, int *i, char *str)
{
	(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		(*i)++;
	pass_spaces(str, i);
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '\0'
		|| str[*i] == '|')
	{
		error5(data, 255, &str[*i], 0);
		return (1);
	}
	return (0);
}

int	pikito_args_checker(t_struct *data, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			pass_quotes(str, &i, str[i]);
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (pikito_args_checker2(data, &i, str))
				return (258);
		}
		else if (str[i] != '\"' || str[i] != '\'')
			i++;
	}
	return (0);
}

int	mega_checker(t_struct *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '9')
		i++;
	if (str[i] == '\0')
		return (1);
	if (quotes_pikito_checker(data, str) == 258)
		return (1);
	if (doble_pipe_checker(data, str) == 258)
		return (1);
	if (pikito_args_checker(data, str) == 258)
		return (1);
	return (0);
}
