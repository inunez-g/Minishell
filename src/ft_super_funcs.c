/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:01:11 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/17 19:10:13 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	super_strncmp(char **str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] != NULL)
	{
		if (!ft_strncmp(str1[i], str2, n))
			return (i);
		i++;
	}
	return (-1);
}

int	super_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**super_dup(char **str1)
{
	char	**str2;
	int		i;

	i = 0;
	str2 = (char **)malloc(sizeof(*str2) * (super_strlen(str1) + 1));
	while (str1[i] != NULL)
	{
		str2[i] = ft_strdup(str1[i]);
		i++;
	}
	str2[i] = NULL;
	return (str2);
}

void	super_printf(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		printf("[%s]\n", str[i]);
		i++;
	}
}
