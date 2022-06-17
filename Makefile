NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = main.c \
	check_elements.c \
	check_extension.c


OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) cub3d.h
	@$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
