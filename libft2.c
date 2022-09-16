/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:26:42 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/16 18:08:05 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strncmp_ms(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s1[0] == '\0' || s2 == NULL)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (1);
	return (0);
}

char	*strjoin_ms(char *str1, char *str2, int boo)
{
	int		len;
	int		len2;
	char	*final;
	int		i;

	len = ft_strlen(str1);
	len2 = ft_strlen(str2);
	final = (char *)malloc(len + len2 + 1);
	i = -1;
	while ( ++i < len && str1 != NULL)
		final[i] = str1[i];
	while (str2 != NULL && i - len < len2)
	{
		final[i] = str2[i - len];
		i++;
	}
	final[i] = '\0';
	free (str1);
	if (boo)
		free (str2);
	return (final);
}
/*
char	*strjoin_ms(char *str, char *str2)
{
	
}*/