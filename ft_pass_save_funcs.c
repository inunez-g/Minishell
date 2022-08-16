/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass_save_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:02:27 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/08 19:05:12 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_words(char *str, int *i)
{
	int	j;

	j = *i;
	pass_word(str, i);
	return (ft_substr(str, j, *i - j));
}

void	pass_word(char *str, int *i)
{
	while (str[*i] != 60 && str[*i] != 62 && str[*i] != 32 && str[*i] != '\0')
	{
		*i = check_quotes(str, *i);
		(*i)++;
	}
}

void	pass_spaces(char *str, int *i)
{
	while (str[*i] == 32)
		(*i)++;
}

void	pass_dollar(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != '$')
	{
		*i = check_quotes(str, *i);
		(*i)++;
	}
}

void	ft_mega_pass(char *str, int *i, char *characters)
{
	while (str[*i] != '\0' && ft_strchr(characters, str[*i]) == 0 && str[*i] != 34)
		(*i)++;
}
