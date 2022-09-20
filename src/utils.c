/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:20:51 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/20 19:52:50 by inunez-g         ###   ########.fr       */
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

void	save_in_outfiles(t_struct *data, char *str, int type)
{
	int	i;
	int	helper;
	int	mode;

	i = 0;
	helper = 0;
	while (str[i] != '\0')
	{
		mode = 1;
		pass_spaces(str, &i);
		if (str[i] == type)
		{
			i++;
			if (str[i] == type)
			{
				i++;
				mode++;
			}
			pass_spaces(str, &i);
			if (type == 60)
			{
				data->infile[helper] = save_words(str, &i);
				data->infile_modes[helper] = mode;
			}
			else if (type == 62)
			{
				data->outfile[helper] = save_words(str, &i);
				data->outfile_modes[helper] = mode;
			}
			helper++;
		}
		else if (str[i] == 60 || str[i] == 62)
			i++;
		else
			pass_word(str, &i);
	}
	if (type == 60)
		data->infile[helper] = NULL;
	else if (type == 62)
		data->outfile[helper] = NULL;
	return ;
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
