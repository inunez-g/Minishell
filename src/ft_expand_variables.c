/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:15:58 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/20 20:12:11 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**set_words(char **final, char *str)
{
	int	i;
	int	nb_words;
	int	index;

	i = 0;
	nb_words = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			index = i;
			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
				i++;
			final[nb_words] = ft_substr(str,index, i - index);
			nb_words++;
		}
		else
		{
			index = i;
			i = check_quotes(str, i) + 1;
			final[nb_words] = ft_substr(str, index, i - index);
			nb_words++;
		}
	}
	return (final);
}

char	**split_words(char *str)
{
	char	**final;
	int		nb_words;

	nb_words = get_words(str);
	final = malloc(sizeof(char *) * (nb_words + 1));
	if (!final)
		error_free("malloc error", NULL);
	final[nb_words] = NULL;
	return (set_words(final, str));
}

char	*ft_dollar(t_struct *data, char *str)
{
	char	**final;
	int		i;
	int		index;
	int		counter;

	counter = count_dollar(str);
	final = malloc(sizeof(char *) * (counter + 1));
	final[counter] = NULL;
	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		index = i;
		pass(str, &i);
		if (!ft_isalnum(str[index]) && str[index] != '_')
			i++;
		final[counter] = expand_var(data, ft_substr(str, index, i - index));
		counter++;
	}
	free(str);
	return (super_join(final));
}

char	*expand_var(t_struct *data, char *word)
{
	int		line;
	int		len;

	if (word[0] == '$')
	{
		word = strjoin_ms(substr_ms(word, 1, ft_strlen(word + 1)), "=", 0);
		line = super_strncmp(data->env, word, ft_strlen(word));
		len = ft_strlen(word);
		free(word);
		if (line != -1)
			return (ft_substr(data->env[line], len, ft_strlen(data->env[line]) - len));
	}
	else
		return (word);
	return (NULL);
}

char	*expand_variables(t_struct *data, char *str)
{
	int		i;
	char	**word;

	word = split_words(str);
	i = 0;
	while (word[i] != NULL)
	{
		if (word[i][0] == '\'')
			word[i] = substr_ms(word[i], 1, ft_strlen(word[i]) - 2);
		else
		{
			if (word[i][0] == '\"')
				word[i] = substr_ms(word[i], 1, ft_strlen(word[i]) - 2);
			word[i] = ft_dollar(data, word[i]);
		}
		i++;
	}
	return (super_join(word));
}
