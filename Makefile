NAME = minishell

CSRC =	main.c \
		ft_split2.c \
		utils.c\
		ft_super_funcs.c\
		ft_builtins_1.c\
		ft_builtins_2.c\
		ft_prepare_clean_funcs.c\
		ft_mode_pipes.c\
		ft_pass_save_funcs.c\
		ft_expand_variables.c\
		libft2.c

OSRC = $(CSRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g#-g3 -fsanitize=address
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
