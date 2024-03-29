NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 
# -fsanitize=address

VPATH = syntax token

INCLUDE = -I./include -I ./libft 

LIBFT = ./libft/libft.a

SRC = main.c \
	check_syntax.c \
	compare.c \
	token_list.c \
	tokenizer.c \
	error.c \
	utils.c

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft $(NAME)

$(NAME): libft $(SRC_OBJ) 
	@$(CC) $(CFLAGS) $(SRC_OBJ) -lreadline $(LIBFT) -o $(NAME) 
	@echo "Compilation completed: $@"

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