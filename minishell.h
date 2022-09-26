/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:13:00 by inunez-g          #+#    #+#             */
/*   Updated: 2022/09/23 21:14:40 by ecamara          ###   ########.fr       */
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
	char	**cmd;
	char	**infile;
	int		*infile_modes;
	char	**outfile;
	int		*outfile_modes;
	char	**env;
	int		fd[2];
	int		inpipe;
	int		fd_infile;
	int		fd_outfile;
	int		status;
	int		error;
}t_struct;

/* ---- PROCCESS ---- */

int		builtins(t_struct *data, int mode);
int		commands_func(t_struct *data);
int		activation_func(t_struct *data, int mode);
void	executions_func(t_struct *data, int mode);

/* --- INOUTFILES ---- */

void	ft_outfile(t_struct *data);
void	infile_helper(t_struct *data, int i, int fd[2]);
void	ft_infile(t_struct *data);
void	save_outfiles(t_struct *data, char *str, int i, int helper);
void	save_infiles(t_struct *data, char *str, int i, int helper);

/* ---- SIGNAL ----- */

void	ft_new_line(void);
void	sighandler(int signal, siginfo_t *a, void *b);

/* ----- INPUT ------ */

void	input(t_struct *data, char *str);
void	mallocs(t_struct *data, char *str);
void	expand_all(t_struct *data);
void	prepare_data(t_struct *data, char *str, int mode);

/* ---- LIBFT2 ---- */

int		strncmp_ms(char *s1, char *s2);
char	*strjoin_ms(char *str1, char *str2, int boo);
char	*super_join(char **str, int counter);
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
int		env_func(t_struct data, int mode);
int		pwd_func(t_struct data, int mode);
void	change(t_struct *data);

char	*cd_func_body(t_struct *data, int pos);
int		unset_func_body(t_struct *data, int i, int line);
int		unset_func(t_struct *data, int helper, int mode);
int		export_func_body(t_struct *data, int i);
int		export_func(t_struct *data, int mode);

void	cd2(t_struct *data, int *pos2, int *pos, char *path);
int		cd3(t_struct *data, char **final_path, int pos, char **path);
void	cd4(t_struct *data, char **final_path, char **path);
void	cd5(t_struct *data, char **final_path, int pos2);
int		cd_func(t_struct *data, int mode, int pos, int pos2);

int		export_helper(char *str);
void	show_export(t_struct *data);
int		checkexit(char *str, t_struct *data);
int		checkpath(t_struct *data);

/* --- MODES_PIPES --- */

void	pipes_func(t_struct *data, int mode);
void	builtin_pipe(t_struct *data);
void	mode2_pipe(t_struct *data);
void	mode1_pipe(t_struct *data);
void	mode0_pipe(t_struct *data);

/* ---- SIGNALS ---- */

void	ft_new_line(void);
void	sighandler(int signal, siginfo_t *a, void *b);

/* ------ PASS ---- */

void	pass_word(char *str, int *i);
void	pass_spaces(char *str, int *i);
void	pass_dollar(char *str, int *i);
void	ft_mega_pass(char *str, int *i, char *characters);
void	pass(char *str, int *i);

/* ------ SAVE ---- */

char	*save_words(char *str, int *i);

/* ---- SPLIT ---- */

int		check_quotes(const char *str, int i);
int		free_memory2(char **split);
int		count_words2(const char *s, char c);
char	**save_word2(const char *s, char c, char **split, int a);
char	**ft_split2(const char *s, char c);

int		free_memory(char **split);

/* ---- ERROR ---- */

void	error2(t_struct *data, char *str, int mode, int activation);
int		error3(t_struct *data, char *str, char *str2, int mode);
void	error4(t_struct *data, char c, int mode);
void	error5(t_struct *data, int mode, char *str, int end);
int		error6(t_struct *data, char *str, int mode, int ret);

int		error7(t_struct *data, int mode, int ret);
int		error8(t_struct *data, char *str, int mode);
int		check_export(t_struct *data, char *str, int mode);
void	error_free(char *str, t_struct *data);

/* ----- SUPER_FUNCS -- */

int		super_strncmp(char **str1, char *str2, int n);
int		super_strlen(char **str);
char	**super_dup(char **str1);
void	super_printf(char **str);

/* ---- UTILS ---- */

int		check_nbr_pointers(char	*str, int type);
int		clean(char *path, int *i, int *index);
char	*clean_path_func(char *path, int i, int index, int j);
void	save_cmd(t_struct *data, char *str);
int		check_nbr_cmd(char *str);

/* ------ CHECKER ------ */

void	pass_quotes(char *str, int *i, char c);
int		pikito_checker(t_struct *data, char *str, int i, char c);
int		quotes_pikito_checker(t_struct *data, char *str);
int		doble_pipe_checker(t_struct *data, char *str);

int		pikito_args_checker(t_struct *data, char *str);
int		mega_checker(t_struct *data, char *str);

/* ------ HEREDOCK ------ */

void	here_dock(t_struct *data, int i);
void	end(char *str, int fd[2]);

#endif
