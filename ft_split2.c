/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:16:00 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/19 11:29:35 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_quotes(const char *str, int i)
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

int free_memory2(char **split)
{
    while (*split)
    {
        free(*split);
        (*split)++;
    }
    free(split);
    return (0);
}

int count_words2(const char *s, char c)
{
    int nbr_words;
    int i;
	int	counter;

    nbr_words = 0;
    i = 0;
	counter = 0;
    while (s[counter])
    {
        if (s[counter] != c && i == 0)
        {
            i = 1;
            nbr_words++;
        }
        else if (s[counter] == c)
            i = 0;
		counter = check_quotes(s, counter);
        counter++;
    }
    return (nbr_words);
}

char    **save_word2(const char *s, char c, char **split, int a)
{
    int r;
    int counter;
    int i;

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
		counter = check_quotes(s, counter);
        counter++;
    }
    split[a] = 0;
    return (split);
}

char    **ft_split2(const char *s, char c)
{
    char    **split;
    int     nbr_words;
    int     a;

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
