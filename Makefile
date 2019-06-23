SRC=lem_in.c \
	rooms.c \
	links.c \
	solution.c \
	bfs.c
NAME=lem_in
LIBFT=lib/libft
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -o $(NAME) $(addprefix src/,$(SRC)) -I include/ -I $(LIBFT) -L $(LIBFT) -lft