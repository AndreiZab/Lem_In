SRC=lem_in.c \
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
NAME=lem-in
LIBFT=lib/libft
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -o $(NAME) $(addprefix src/,$(SRC)) -I include/ -I $(LIBFT) -L $(LIBFT) -lft

clean:
	make -C $(LIBFT) fclean

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)