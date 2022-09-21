/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:16:00 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/21 19:46:58 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(const char *str, int i)
{
	if (str[i] == 34)
	{
		while (str[++i] && str[i] != 34)
			continue ;
	}
	else if (str[i] == 39)
	{
		while (str[++i] && str[i] != 39)
			continue ;
	}
	return (i);
}

int	free_memory2(char **split)
{
	while (*split)
	{
		free(*split);
		(*split)++;
	}
	free(split);
	return (0);
}

int	count_words2(const char *s, char c)
{
	int	nbr_words;
	int	i;
	int	check;

	nbr_words = 0;
	i = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			check = 1;
			nbr_words++;
		}
		else if (s[i] == c)
			check = 0;
		i = check_quotes(s, i);
		i++;
	}
	return (nbr_words);
}

char	**save_word2(const char *s, char c, char **split, int a)
{
	int	r;
	int	counter;
	int	i;

	counter = 0;
	r = 0;
	while (a < count_words2(s, c))
	{
		if (s[counter] != c && r == 0)
		{
			r = 1;
			i = counter;
		}
		else if (((s[counter] == c) || (s[counter] == '\0')) && r == 1)
		{
			r = 0;
			split[a] = ft_substr(s, i, (counter - i));
			if (!split[a])
				free_memory2(split);
			a++;
		}
		counter = check_quotes(s, counter) + 1;
	}
	split[a] = 0;
	return (split);
}

char	**ft_split2(const char *s, char c)
{
	char	**split;
	int		nbr_words;
	int		a;

	a = 0;
	if (!s)
		return (0);
	else
	{
		nbr_words = count_words2(s, c);
		split = (char **)malloc((nbr_words + 1) * sizeof(char *));
		if (!split)
			return (0);
	}
	return (save_word2(s, c, split, a));
}
