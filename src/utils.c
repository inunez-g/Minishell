/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:20:51 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/23 17:00:36 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_nbr_pointers(char	*str, int type)
{
	int	nbr_pointers;
	int	i;

	i = 0;
	nbr_pointers = 0;
	while (str[i])
	{
		if (str[i] == type)
		{
			nbr_pointers += 1;
			if (str[i + 1] == type)
				i++;
		}
		i = check_quotes(str, i);
		i++;
	}
	return (nbr_pointers);
}

int	clean(char *path, int *i, int *index)
{
	if (path[(*i) + 1] == '.' && path[(*i) + 2] == '.')
	{
		(*i) += 3;
		(*index) = (*i);
		return (1);
	}
	return (0);
}

char	*clean_path_func(char *path, int i, int index, int j)
{
	char	*clean_path;

	clean_path = ft_calloc(ft_strlen(path) + 1, sizeof(char));
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			if (!clean(path, &i, &index))
			{
				while (index < i)
					clean_path[j++] = path[index++];
				i++;
			}
		}
		else
			i++;
		if (path[i] == '\0')
		{
			while (index < i)
				clean_path[j++] = path[index++];
		}
	}
	free(path);
	return (clean_path);
}

void	save_cmd(t_struct *data, char *str)
{
	int	i;
	int	helper;

	i = 0;
	helper = 0;
	while (str[i] != '\0')
	{
		pass_spaces(str, &i);
		if (str[i] == 60 || str[i] == 62)
		{
			i++;
			if (str[i] == 60 || str[i] == 62)
				i++;
			pass_spaces(str, &i);
			pass_word(str, &i);
		}
		else if (str[i] != '\0')
		{
			data->cmd[helper] = save_words(str, &i);
			helper++;
		}
	}
	data->cmd[helper] = NULL;
	return ;
}

int	check_nbr_cmd(char *str)
{
	int	i;
	int	helper;

	i = 0;
	helper = 0;
	while (str[i] != '\0')
	{
		pass_spaces(str, &i);
		if (str[i] == 60 || str[i] == 62)
		{
			i++;
			if (str[i] == 60 || str[i] == 62)
				i++;
			pass_spaces(str, &i);
			pass_word(str, &i);
		}
		else if (str[i] != '\0')
		{
			helper++;
			pass_word(str, &i);
		}
	}
	return (helper);
}
