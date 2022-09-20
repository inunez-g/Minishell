/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:03 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/20 19:18:53 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_words(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while(str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
				i++;
			n++;
		}
		else
		{
			i = check_quotes(str, i);
			i++;
			n++;
		}
	}
	return (n);
}

int	count_dollar(char *str)
{
	int	i;
	int	counter;
	int	check;

	counter = 1;
	i = 0;
	check = 0;
	while(str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_') && i != 0)
		{
			counter++;
			i++;
			check = 1;
		}
		else
		{
			i++;
			if (check == 1)
			{
				counter++;
				check = 0;
			}
		}
	}
	return (counter);
}
