/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:15:58 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/01 19:59:15 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**temp_dollar(char *str)
{
	char	**final;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
				i++;
			counter++;
		}
		else
		{
			i = check_quotes(str, i);
			i++;
			counter++;
		}
	}
	final = malloc(sizeof(char *) * (counter + 1));
	final[counter] = NULL;
	i = 0;
	return (temp_dollar2(str, final, i));
}

char	**temp_dollar2(char*str, char **final, int i)
{
	int	counter;
	int	index;

	counter = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			index = i;
			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
				i++;
			final[counter] = ft_substr(str, index, i - index);
			counter++;
		}
		else
		{
			index = i;
			i = check_quotes(str, i);
			i++;
			final[counter] = ft_substr(str, index, i - index);
			counter++;
		}
	}
	return (final);
}

char	*ft_dollar(t_struct *data, char *str)
{
	char	**final;
	int		i;
	int		counter;

	i = 0;
	counter = 1;
	while (str[i])
	{
		if (ft_strchr("$-+@#.,;: '", str[i]) != 0)
		{
			counter++;
			if (ft_strchr("-+@#.,;: '", str[i]) != 0 \
				&& ft_strchr("-+@#.,;: '", str[i + 1]) == 0)
				counter++;
		}
		i++;
	}
	final = malloc(sizeof(char *) * (counter + 1));
	final[counter] = NULL;
	return (ft_dollar2(data, str, final));
}

char	*ft_dollar2(t_struct *data, char *str, char **final)
{
	int		i;
	int		counter;
	int		index;
	char	*helper;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		index = i;
		i++;
		if (ft_strchr("-+@#.,;: '", str[index]) == 0)
			ft_mega_pass(str, &i, "$-+@#.,;:'");
		final[counter] = expand_var(data, ft_substr(str, index, i - index));
		//printf("str -> %s\n", str);
		//printf("final -> %s\n", final[counter]);
		//if (str[i] == '\'' || str[i] == '\"')
			//i++;
		counter++;
	}
	helper = join_variables(final, counter);
	return (helper);
}

char	*join_variables(char **word, int len)
{
	int		i;
	char	*str;
	char	*helper;

	str = "";
	i = 0;
	while (i < len)
	{
		if (word[i] != NULL)
		{
			helper = ft_strjoin(str, word[i]);
			str = helper;
		}
		i++;
	}
	return (str);
}

char	*expand_var(t_struct *data, char *word)
{
	int		line;
	int		len;

	if (word[0] == '$')
	{
		word = ft_strjoin(word + 1, "=");
		line = super_strncmp(data->env, word, ft_strlen(word));
		len = ft_strlen(word);
		if (line != -1)
		{
			free(word);
			word = NULL;
			word = ft_substr(data->env[line], \
				len, ft_strlen(data->env[line]) - len);
		}
		else
			word = NULL;
	}
	return (word);
}

char	*expand_variables(t_struct *data, char *str)
{
	int		i;
	char	**word;
	char	*helper;

	word = temp_dollar(str);
	i = 0;
	while (word[i] != NULL)
	{
		if (word[i][0] == '\'')
		{
			helper = ft_substr(word[i], 1, ft_strlen(word[i]) - 2);
			free(word[i]);
			word[i] = helper;
		}
		else
		{
			if (word[i][0] == '\"')
			{
				helper = ft_substr(word[i], 1, ft_strlen(word[i]) - 2);
				free(word[i]);
				word[i] = ft_strdup(helper);
			}
			word[i] = ft_dollar(data, word[i]);
		}
		i++;
	}
	helper = join_variables(word, super_strlen(word));
	return (helper);
}
