/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:41:26 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 18:14:33 by inunez-g         ###   ########.fr       */
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

void	ft_infile(t_struct *data)
{
	int		i;
	int		fd;
	int		fd2[2];
	char	*temp;
	char	*str;

	str = NULL;
	temp = NULL;
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
		{
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
				pipe(fd2);
				write(fd2[1], str, ft_strlen(str));
				data->inpipe = fd2[0];
			}
			close(fd2[1]);
		}
		i++;
	}
}
