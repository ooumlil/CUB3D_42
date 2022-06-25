NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = parsing/utils.c \
	parsing/utils2.c \
	parsing/ft_split.c \
	parsing/check_extension.c \
	parsing/map_filling.c \
	parsing/map_parsing.c \
	parsing/map_checking.c \
	parsing/colors_and_new_line.c \
	gameplay/window_creation.c \
	gameplay/take_keys.c\
	main.c


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
