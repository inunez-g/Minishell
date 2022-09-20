/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:26:42 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/20 20:00:08 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (++i < len && str1 != NULL)
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

char	*super_join(char **str)
{
	int		i;
	char	*final;

	i = 0;
	final = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		final = strjoin_ms(final, str[i], 1);
		i++;
	}
	free(str);
	return (final);
}

char	*substr_ms(char *s, unsigned int start, size_t	len)
{
	char	*final_str;
	size_t	i;
	size_t	j;
	size_t	reallen;

	i = start;
	j = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < (start + len))
		reallen = (ft_strlen(s) - start);
	else
		reallen = len;
	if (ft_strlen(s) < start)
		reallen = 0;
	final_str = (char *)malloc((reallen + 1) * (sizeof(char)));
	if (!final_str)
		return (0);
	while (i < ft_strlen(s) && j < reallen)
		final_str[j++] = s[i++];
	final_str[j] = '\0';
	free (s);
	return (final_str);
}

int	strchr_ms(char *str, char c)
{
	while (*str != '\0' && c != *str)
		str++;
	if (c == *str)
		return (1);
	return (0);
}
