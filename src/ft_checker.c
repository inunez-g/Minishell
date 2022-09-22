/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:31:12 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/22 17:37:54 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_quotes(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
}

int	pikito_checker(t_struct *data, char *str, int i, char c)
{
	if (str[i + 1] == c && str[i + 1] != '\0' && str[i + 2] == c)
	{
		if (str[i] == '>')
		{
			error5(data, 258, &str[i], 0);
			return (258);
		}
	}
	else if (str[i + 1] == c && str[i + 2] != c)
		return (i + 1);
	else if (str[i + 1] != c)
		return (i);
	return (i);
}

int	quotes_pikito_checker(t_struct *data, char *str)
{
	int	i;
	int	helper;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			helper = str[i];
			pass_quotes(str, &i, str[i]);
			if (str[i] == '\0')
			{
				error4(data, helper, 258);
				return (258);
			}
		}
		if (str[i] == '<' || str[i] == '>')
		{
			i = pikito_checker(data, str, i, str[i]);
			if (i == 258)
				return (258);
		}
		i++;
	}
	return (0);
}

int	doble_pipe_checker(t_struct *data, char *str)
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
		if (str[i] == '|')
		{
			while (str[++i] == ' ')
				continue ;
			if (str[i] == '|')
			{
				error5(data, 255, &str[i], 0);
				return (258);
			}
		}
		if ((str[i] != '\"' || str[i] != '\'') && str[i] != '\0')
			i++;
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
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i] == '<' || str[i] == '>')
				i++;
			pass_spaces(str, &i);
			if (str[i] == '<' || str[i] == '>' || str[i] == '\0'
				|| str[i] == '|')
			{
				error5(data, 255, &str[i], 0);
				return (258);
			}
		}
		if (str[i] != '\"' || str[i] != '\'')
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
