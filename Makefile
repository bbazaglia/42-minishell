NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -w
# -fsanitize=address

VPATH = builtin tree parse heredoc execute environ

INCLUDE = -I./include -I ./libft 

LIBFT = ./libft/libft.a

SRC = main.c \
	check_syntax.c \
	tokenizer.c \
	tokenizer_utils.c \
	utils.c \
	check_heredoc.c \
	get_set_env.c \
	get_set_env_utils.c \
	signal.c \
	build_bin_tree.c \
	print_tree.c \
	execution.c \
	parser.c \
	split_list.c \
	execution_utils.c \
	echo.c \
	cd.c \
	exit.c \
	pwd.c

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft $(NAME)

$(NAME): libft $(SRC_OBJ) 
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT) -o $(NAME) 
	@echo "Compilation completed: $@"

a.out: libft $(SRC_OBJ)
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT)

libft:
	make -C ./libft

$(OBJ)/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<\n)"

clean: 
	@make -C ./libft clean --silent
	@rm -rf $(OBJ)
	@echo "objects removed" 

fclean: clean
	@make -C ./libft fclean --silent 
	@rm -f $(NAME) $(BONUS) a.out
	@echo "executable removed"

re: fclean all

.PHONY: all clean fclean re libft