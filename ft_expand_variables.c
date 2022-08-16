/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:15:58 by inunez-g          #+#    #+#             */
/*   Updated: 2022/08/08 20:10:45 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_dollar(char *str)
{
	char	**final;
	int		i;
	int		index;
	int		counter;

	i = 0;
	counter = 1; 
	while(str[i])
	{
		if (ft_strchr("$-+@#.,;:", str[i]) != 0 && i != 0 && (str[0] != 34 && str[1] != '$'))
			counter++;
		i++;
	}
	final = malloc(sizeof(char *) * (counter + 1));
	final[counter] = NULL;
	i = 0;
	counter = 0;
	while (str[i])
	{
		index = i;
		i++;
		ft_mega_pass(str, &i, "$-+@#.,;:");
		final[counter] = ft_substr(str, index, i - index);
		counter++;
	}
	return (final);
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
	return(str);
}

char	*expand_variables(t_struct *data, char *str)
{
	int		i;
	char	**word;
	int		line;
	int		len;

	word = ft_dollar(str);
	i = 0;
	while (word[i] != NULL)
	{
		if (word[i][0] == '$')
		{
			word[i] = ft_strjoin(word[i] + 1, "=");
			line = super_strncmp(data->env, word[i], ft_strlen(word[i]));
			len = ft_strlen(word[i]);
			free(word[i]);
			word[i] = NULL;
			if (line != -1)
				word[i] = ft_substr(data->env[line], len, ft_strlen(data->env[line]) - len);
		}
		i++;
	}
	free(str);
	str = join_variables(word, i);
	return (str);
}
