/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:41:26 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 19:53:34 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_outfile(t_struct *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->outfile[i])
	{
		if (data->outfile_modes[i] == 1)
			fd = open(data->outfile[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(data->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->outfile[i + 1] == NULL)
			data->fd_outfile = fd;
		else
			close(fd);
		i++;
	}
}

void	infile_helper(t_struct *data, int i)
{
	char	*temp;
	int		fd[2];
	char	*str;

	temp = NULL;
	str = NULL;
	while (1)
	{
		temp = readline("> ");
		if (!strncmp_ms(temp, data->infile[i]) || temp == NULL)
			break ;
		str = strjoin_ms(str, temp, 1);
		str = strjoin_ms(str, "\n", 0);
	}
	free(temp);
	if (data->infile[i + 1] == NULL)
	{
		pipe(fd);
		write(fd[1], str, ft_strlen(str));
		data->inpipe = fd[0];
	}
	free (str);
	close(fd[1]);
}

void	ft_infile(t_struct *data)
{
	int		i;
	int		fd;

	i = 0;
	while (data->infile[i])
	{
		if (data->infile_modes[i] == 1)
		{
			fd = open(data->infile[i], O_RDONLY, 0644);
			if (fd == -1)
				error2(data, data->infile[i], 1, g_proccess == 2);
			if (data->infile[i + 1] == NULL)
				data->fd_infile = fd;
		}
		else
			infile_helper(data, i);
		i++;
	}
}

void	save_infiles(t_struct *data, char *str, int i, int helper)
{
	int	mode;

	while (str[i])
	{
		mode = 1;
		pass_spaces(str, &i);
		if (str[i] == '<')
		{
			if (str[++i] == '<')
			{
				i++;
				mode++;
			}
			pass_spaces(str, &i);
			data->infile[helper] = save_words(str, &i);
			data->infile_modes[helper] = mode;
			helper++;
		}
		else if (str[i] == '>')
			i++;
		else
			pass_word(str, &i);
	}
	data->infile[helper] = NULL;
}

void	save_outfiles(t_struct *data, char *str, int i, int helper)
{
	int	mode;

	while (str[i])
	{
		mode = 1;
		pass_spaces(str, &i);
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				i++;
				mode++;
			}
			pass_spaces(str, &i);
			data->outfile[helper] = save_words(str, &i);
			data->outfile_modes[helper] = mode;
			helper++;
		}
		else if (str[i] == '<')
			i++;
		else
			pass_word(str, &i);
	}
	data->outfile[helper] = NULL;
}
