/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:35:54 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/18 19:09:51 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtins(t_struct *data, int mode)
{
	if (echo_func(*data, mode))
		return (1);
	else if (exit_func(*data, mode))
		return(1);
	else if (env_func(*data, mode))
		return(1);
	else if (pwd_func(*data, mode))
		return(1);
	else if (cd_func(data, mode))
		return (1);
	else if (export_func(data, mode))
		return(1);
	else if (unset_func(data, 0, mode))
		return(1);
	return(0);
}

int commands_func(t_struct *data)
{
	char	*final_path;
	char	**path;
	char	*command;
	int		pos;
	int		i;

	i = 0;
	if (data->cmd[0] == NULL)
			exit (0);
	command = ft_strjoin("/", data->cmd[0]);
	pos = super_strncmp(data->env, "PATH=", 5);
	path = ft_split(data->env[pos] + 5, ':');
	while(path[i] != NULL)
	{
		final_path = ft_strjoin(path[i], command);
		if (access(final_path, X_OK) == -1)
		{
			free(final_path);
			i++;
		}
		else
		{
			printf("%s %s\n",path[i],command);
			execve(ft_strjoin(path[i],command), data->cmd, data->env);
		}
	}
	write(1, "command not found\n", 18);
	exit (0);
}

int	activation_func(t_struct *data, int mode)
{
	if (mode != 3)
		return (1);
	if (!builtins(data, 0))
		return (1);
	ft_outfile(data);
	ft_infile(data);
	builtin_pipe(data);
	return (0);
}

void    executions_func(t_struct *data, int mode, int command_nbr)
{
    int pid;
    int status;
	//int	fd[2];

	(void) mode;
 	//if (activation_func(data, mode))
    //{
		
		//pipe(data->fd);
		pid = fork();
    	if (pid == -1)
		    return ;
		if (pid == 0)
		{
			//close(fd[0]);
			g_proccess = 2;
			//ft_outfile(data);
			//ft_infile(data);
			//ft_putnbr_fd(mode, 0);
			//pipes_func(data, mode, fd);
			//write (0, "pipe\n", 5);
			//if (!builtins(data, 1))
	    	//printf("Command nbr %d\n", command_nbr);
			if (data->total_cmds == 0)
			{
				printf("Entro en comando 0");
				dup2(data->fd[1], 1);
				close(data->fd[0]);
				close(data->fd[1]);
			}
			else if (command_nbr == data->total_cmds - 1)
			{
				if (data->total_cmds == 2)
				{
					printf("Entro en comando 2");
					dup2(data->fd[0],0);
					close(data->fd[1]);
					close(data->fd[0]);
				}
				else
				{
					dup2(data->inpipe, 0);
					close(data->fd[1]);
					close(data->fd[0]);
				}
			}
			else
			{
				dup2(data->inpipe, 0);
				dup2(data->fd[1], 1);
				close(data->fd[0]);
				close(data->fd[1]);
			}
			commands_func(data);
			//exit (0);
		}
		else
		{
			if (data->total_cmds > 1)
				close(data->fd[1]);
            waitpid(pid, &status, 0);
			//write (0, "2pipe\n", 6);;
			g_proccess = 1;
			data->status = WEXITSTATUS(status);
			//if (data->inpipe != -1)
			//	close(data->inpipe);
			//dup2(data->fd[0], data->inpipe);//data->inpipe = data->fd[0];
			//close(fd[1]);
			if(data->total_cmds > 2)
			{
				data->inpipe = dup(data->fd[0]);
				close(data->fd[0]);
				pipe(data->fd);
			}
			
			//data->inpipe = fd[0];
			//if (mode == 2 || mode == 3)
			//	close(data->inpipe);
			//close(data->fd[0]);
			//data->fd_outfile = -1;
			//data->fd_infile = -1;
        }
		//close(data->fd[0]);
		//close(data->fd[1]);
 //   }
}