/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:13:00 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/20 19:07:18 by ecamara          ###   ########.fr       */
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

int	g_proccess;

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

void	write_pipe(int fd);
int export_helper(char *str);

/* ---- PROCCESS ---- */

int 	builtins(t_struct *data, int mode);
int 	commands_func(t_struct *data);
int		activation_func(t_struct *data, int mode);
void	executions_func(t_struct *data, int mode);

/* --- INOUTFILES ---- */

void	ft_outfile(t_struct *data);
void	ft_infile(t_struct *data);

/* ---- SIGNAL ----- */

void	sighandler(int signal, siginfo_t *a, void *b);
void	ft_new_line(void);

/* ----- INPUT ------ */

void	input(t_struct *data, char *str);
void	prepare_data(t_struct *data, char *str, int mode);
void	mallocs(t_struct *data, char *str);
void	expand_all(t_struct *data);
char	*clean_path_func(char *path);

/* ---- LIBFT2 ---- */

char	*super_join(char **str);
char	*strjoin_ms(char *str1, char *str2, int boo);
int		strncmp_ms(char *s1, char *s2);
char	*substr_ms(char *s, unsigned int start, size_t	len);
int		strchr_ms(char *str, char c);

/* -- EXPAND_VARIABLE -- */

char	**set_words(char **final, char *str);
char	**split_words(char *str);
char	*ft_dollar(t_struct *data, char *str);
char	*expand_var(t_struct *data, char *word);
char	*expand_variables(t_struct *data, char *str);

/* - EXPAND_VARIABLE_AUX - */

int		get_words(char *str);
int		count_dollar(char *str);

/* -- BUILTINTS -- */

int		echo_func(t_struct data, int mode);
int		exit_func(t_struct data, int mode);
int		env_func(t_struct data, int	mode);
int		pwd_func(t_struct data, int	mode);
int		cd_func(t_struct *data, int	mode);

char	*cd_func_body(t_struct *data, int pos);
int		unset_func_body(t_struct *data, int i, int line);
int		unset_func(t_struct *data, int helper, int mode);
int		export_func_body(t_struct *data, int i);
int		export_func(t_struct *data, int mode);


/* --- MODES_PIPES --- */

void	pipes_func(t_struct *data, int mode, int fd[2]);
void	builtin_pipe(t_struct *data);
void	mode2_pipe(t_struct *data, int fd[2]);
void	mode1_pipe(t_struct *data, int fd[2]);
void	mode0_pipe(t_struct *data, int fd[2]);

/* ---- SIGNALS ---- */

void	ft_new_line(void);
void	sighandler(int signal, siginfo_t *a, void *b);

/* ------ PASS ---- */

void	ft_mega_pass(char *str, int *i, char *characters);
void	pass_word(char *str, int *i);
void	pass_spaces(char *str, int *i);
void	pass_dollar(char *str, int *i);
void	ft_mega_pass(char *str, int *i, char *characters);
char	*save_words(char *str, int *i);
void	pass(char *str, int *i);

/* ---- SPLIT ---- */

char	**ft_split2(const char *s, char c);
int		check_quotes(const char *str, int i);
int		free_memory(char **split);

/* ---- ERROR ---- */

int		check_export(t_struct *data, char *str, int mode);
void	error5(t_struct *data, int mode);
void	error4(t_struct *data, char c, int mode);
void	error3(t_struct *data, char *str, char *str2, int mode);
void	error2(t_struct *data, char *str, int mode, int activation);
void	error_free(char *str, t_struct *data);

/* ----- SUPER_FUNCS -- */

void	super_printf(char **str);
char	**super_dup(char **str1);
int		super_strlen(char **str);
int		super_strncmp(char **str1, char *str2, int n);

/* ---- UTILS ---- */

int		check_nbr_pointers(char	*str, int type);
void	save_in_outfiles(t_struct *data, char *str, int type);
void    save_cmd(t_struct *data, char *str);
int		check_nbr_cmd(char *str);

#endif
