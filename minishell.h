/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:13:00 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/09 11:08:40 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_struct
{
	char **cmd;
	char **infile;
	int *infile_modes;
	char **outfile;
	int *outfile_modes;
	char **env;
	int fd[2];
	int inpipe;
	int fd_infile;
	int fd_outfile;
	int	status;
}t_struct;

int		echo_func(t_struct data, int mode);

int		exit_func(t_struct data, int mode);

int		env_func(t_struct data, int mode);

int		pwd_func(t_struct data, int mode);

char	*cd_func_body(t_struct *data, int pos);

int		cd_func(t_struct *data, int mode);

int		unset_func_body(t_struct *data, int i, int line);

int		unset_func(t_struct *data, int helper, int mode);

int		export_func_body(t_struct *data, int i);

int		export_func(t_struct *data, int mode);

int		super_strncmp(char **str1, char *str2, int n);

int		super_strlen(char **str);

char	**super_dup(char **str1);

void	ft_new_line(void);

void	sighandler(int signal, siginfo_t *a, void *b);

char	*clean_path_func(char *path);

void	super_printf(char **str);

int		export_helper(char *str);

void	executions_func(t_struct *data, int mode);

void	prepare_data(t_struct *data, char *str, int mode);

void	prepare_pipes(t_struct *data, char *str);

char	*ft_dollar(t_struct *data, char *str);

char	**save_word2(const char *s, char c, char **split, int a);

int		count_words2(const char *s, char c);

int		free_memory2(char **split);

int		check_quotes(const char *str, int i);

char	**ft_split2(const char *s, char c);

int		check_nbr_pointers(char *str, int type);

char	*save_words(char *str, int *i);

void	save_in_outfiles(t_struct *data, char *str, int type);

char	*expand_variables(t_struct *data, char *str);

char	*join_variables(char **word, int len);

void	pass_spaces(char *str, int *i);

void	pass_word(char *str, int *i);

void	save_cmd(t_struct *data, char *str);

void	pass_dollar(char *str, int *i);

int		check_nbr_cmd(char *str);
	
void	ft_mega_pass(char *str, int *i, char *characters);

void    builtin_pipe(t_struct *data);

void	mode2_pipe(t_struct *data);

void	mode1_pipe(t_struct *data);

void	mode0_pipe(t_struct *data);

void	ft_outfile(t_struct *data);

char	*clean_exp_vars(char *word);

char    *expand_var(t_struct *data, char *word);

void    pipes_func(t_struct *data, int mode);

void    ft_infile(t_struct *data);

int builtins(t_struct *data, int mode);
#endif
