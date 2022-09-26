NAME = minishell

CSRC =	src/main.c						\
		src/ft_split2.c					\
		src/utils.c						\
		src/ft_super_funcs.c			\
		src/ft_builtins_1.c				\
		src/ft_builtins_2.c				\
		src/ft_builtins_3.c				\
		src/ft_builtins_4.c				\
		src/ft_mode_pipes.c				\
		src/ft_pass_funcs.c				\
		src/ft_save_funcs.c				\
		src/ft_expand_variables.c		\
		src/libft2.c					\
		src/signals.c					\
		src/inoutfile.c					\
		src/input.c						\
		src/error.c						\
		src/error2.c					\
		src/ft_expand_var_aux.c			\
		src/proccess.c					\
		src/heredock.c					\
		src/ft_checker.c				\
		src/ft_checker2.c

OSRC = $(CSRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
LDFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
CPPFLAGS= -I/Users/$(USER)/.brew/opt/readline/include
GCCCMD = gcc

LIBFT = libft/libft.all

all: $(NAME)

%.o: %.c
	@$(GCCCMD) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(NAME): $(OSRC)
	@echo "\033[33mCompiling libft...\033[0m"
	@make -C libft
	@make -C libft/ bonus
	@mv libft/libft.a .
	@echo "\033[33mCompiling minishell project...\033[0m"
	@$(GCCCMD) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) libft.a $^ -o $(NAME)
	@echo "\033[92mminishell has been successfully compiled!\033[0m"

clean:
	@rm -f $(OSRC)
	@rm -f libft.a
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
