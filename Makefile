NAME = lem-in
SRC = lem_in.c \
	rooms.c \
	links.c \
	paths.c \
	solution.c \
	collisions.c \
	collisions_2.c \
	lock.c \
	migration.c \
	validation.c \
	parse_rooms.c \
	parse_lins.c
CC = gcc -Wall -Wextra -Werror

HEAD_DIR = ./include/
HEAD = ./include/ft_lem_in.h

LIBFT = ./lib/libft/libft.a
LIBFT_DIR = ./lib/libft/
LIBRARIES = -L ./lib/libft/

INCLUDES = -I ./include/ -I$(LIBFT_DIR)

OBJ_DIR = ./obj/
OBJECTS = $(patsubst %.c, %.o, $(SRC))
OBJ	= $(addprefix ./obj/, $(OBJECTS))


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBRARIES) $(LIBFT)
	@printf "%-54c\rDone !\n" ' '

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : ./src/%.c $(HEAD)
	@$(CC) -c $(INCLUDES) $< -o $@
	@printf "Compiling... %-21s => %-21s\r" $^ $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean